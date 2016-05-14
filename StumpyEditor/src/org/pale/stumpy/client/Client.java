package org.pale.stumpy.client;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.UnknownHostException;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.SocketChannel;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Set;
import java.util.concurrent.ExecutionException;

import javax.swing.SwingWorker;

import org.pale.stumpy.components.PrimComponentType;
import org.pale.stumpy.main.TopController;
import org.pale.stumpy.model.ComponentTypeRegistry;
import org.pale.stumpy.model.UnknownComponentTypeException;

/**
 * Underlying client class for communicating with the server, using non-blocking sockets
 * @author white
 *
 */
public class Client {
    private SocketChannel socket;
    private Selector selector;
    private boolean isValid;
    private ByteBuffer inBuf = ByteBuffer.allocate(1024);
    private ByteBuffer outBuf = ByteBuffer.allocate(1024);
    
    public static class Status {
        Status(boolean ok,String error){
            this.ok = ok;
            this.error = error;
        }
        public boolean ok;
        public String error;
    }
    
    public  interface StatusListener {
        public void newStatus(Status s);
    }
    static List<StatusListener> statusListeners = new LinkedList<StatusListener>();
    
    public static void addStatusListener(StatusListener s){
        statusListeners.add(s);
    }
    
    public static void notifyStatusListeners(boolean ok,String error){
        Status s = new Status(ok,error);
        for(StatusListener sl : statusListeners){
            sl.newStatus(s);
        }
    }
    
    private static Client INSTANCE;
    
    public static boolean isConnected(){
        return INSTANCE!=null;
    }
    
    public static void create(String host, int port){
        if(INSTANCE!=null){
            notifyStatusListeners(false, "already connected - disconnect first");
            return;
        }
        INSTANCE = new Client(host,port);
        if(!INSTANCE.isValid){
            INSTANCE.disconnect();
        }else{
            /// send command to fetch prim names
            INSTANCE.sendCmd("startprims");
        }
    }
    
    public static void destroy(){
        if(INSTANCE==null){
            notifyStatusListeners(false, "not connected");
            return;
        }
        INSTANCE.disconnect();
        notifyStatusListeners(false, "link closed down");
        
    }

    
    public static Client getInstance(){
        return INSTANCE;
    }
    
    
    
    
    private void setError(String s){
        isValid = false;
        notifyStatusListeners(false,s);
    }
    
    public boolean isValid(){
        return isValid;
    }
    
    /**
     * Create the client and initialise the connection. Afterwards, isValid() should be true.
     * If there was a problem, isValid will be false. Is a singleton which only exists sometimes.
     * @param host
     * @param port
     */
    private Client(String host,int port){
        setError("not yet initialised");
        try {
            socket = SocketChannel.open();
            socket.configureBlocking(false);
            socket.connect(new InetSocketAddress(host,port)); // non blocking
            
            while(!socket.finishConnect()); // busy wait for connection to finish
            
            // create a selector and register our channel with it for read events
            selector = Selector.open();
            socket.register(selector, SelectionKey.OP_READ);
            isValid = true;
            notifyStatusListeners(true,"client connected");
            
        } catch (UnknownHostException e) {
            setError("unknown host");
            disconnect();
        } catch (IOException e) {
            setError("IO exception - server not running?");
            disconnect();
        }
        
    }
    
    private void disconnect() {
        INSTANCE = null;
        try {
            if(socket!=null)
                socket.close();
            if(selector!=null)
                selector.close();
        } catch (IOException e){
        	e.printStackTrace();
        }
        TopController.getInstance().notifyRefreshables();
    }
    
    /**
     * The result from a sequence of communications commands. If everything worked, code will be zero.
     * The first command which causes a problem will make the sequence stop, and code and errorMsg will
     * have details. 
     * @author white
     *
     */
    public class CommsResult {
        int code;
        String errorMsg;
        
        CommsResult(int code,String msg){
            this.code=code;
            errorMsg=msg;
        }
        
        /**
         * Return the error code (zero for OK)
         * @return code
         */
        public int getCode(){
            return code;
        }
        /**
         * Return an error message
         * @return message
         */
        public String getErrorMsg(){
            return errorMsg;
        }
    }
    
    /**
     * The swing worker for the asynchronous task of sending a load of commands to the
     * server. Note the template: CommsResult is the final result, Void is intermediate results via publish()
     * (which we don't use).
     * @author white
     *
     */
    public class CommsTask extends SwingWorker<CommsResult,Void> {
        
        private List<String> commands;

        /**
         * Construct the task with a list of commands to send to the server
         * @param commands list to send
         */
        CommsTask(List<String> commands){
            this.commands = commands;
        }
        
        private CommsResult processSelectorLoop(){
            for(;;){
                try {
                    selector.select(1000);
                } catch (IOException e) {
                    return new CommsResult(501,"IO exception in select");
                }
                Set<SelectionKey> keys = selector.selectedKeys();
                Iterator<SelectionKey> i = keys.iterator();
                while(i.hasNext()){
                    SelectionKey k = i.next();
                    if(k.isReadable()){
                        try {
                            inBuf.clear();
                            int count = socket.read(inBuf);
                            if(count<0){
                                disconnect();
                                return new CommsResult(520,"server closed connection");
                            }
                            inBuf.flip();
                            System.out.println("Read: "+inBuf.toString());

                            // convert byte array to string, ugly and screws up
                            // encoding but that doesn't matter for us.
                            byte[] arr = new byte[inBuf.remaining()];
                            inBuf.get(arr);
                            String s = new String(arr);
                            
                            
                            System.out.println("Read: "+s);
                            String bits[] = s.split("\\s+",2);
                            if(bits[0].length()!=3)
                                return new CommsResult(504,"return from server is invalid");
                            if(bits[0].replaceAll("\\d+","").length() > 0)
                                return new CommsResult(505,"return from server has non-numeric code");
                            int code = Integer.parseInt(bits[0]);
                            System.out.println(code);
                            // hacky stuff for adding primitive mesh names (code 401/402)
                            if(code == 401){
                            	System.out.println("Got prim name: "+bits[1]);
                            	addPrimitive(bits[1]);
                            	sendCmd("nextprim");
                            	return new CommsResult(0,"prim added");
                            }else if(code == 402){ // that was the last one
                            	return new CommsResult(0,"prims done");
                            }
                            
                            return new CommsResult(code,bits[1]);
                            
                            
                        } catch (IOException e) {
                            return new CommsResult(503,"IO exception in read");
                        } catch (UnknownComponentTypeException e) {
							// TODO Auto-generated catch block
							return new CommsResult(504, "add primitive failed to find type");
						}
                    }
                }
            }
            
        }



		@Override
        protected CommsResult doInBackground() throws Exception {
            CommsResult r=new CommsResult(502,"return never processed");
            for(String cmd: commands){
                System.out.println("sending "+cmd);
                outBuf.clear();
                outBuf.put(cmd.getBytes());
                outBuf.put((byte) 0); // terminate!
                outBuf.flip();
                while(outBuf.hasRemaining())
                    socket.write(outBuf); // non blocking, but the loop will deal with it.
                
                // handle read responses
                
                r = processSelectorLoop();
                System.out.println("Code: "+r.getCode());
                if(r.getCode()!=0)
                    break;
            }
            return r;
        }
        
    }
    
    /**
     * Send a set of commands and await a reply. If the reply is not valid (i.e. the return code is non-zero) or
     * another error occurred, deal. Will use a swing worker and run asynchronously.
     * @param s
     */
    public void send(List<String> commands){
        CommsResult r = new CommsResult(510,"no processing occurred");
        if(!isConnected()){
            r = new CommsResult(520,"not connected!");
            return;
        }
        CommsTask t = new CommsTask(commands);
         r = new CommsResult(510,"no processing occurred");
        try {
            t.execute();
            r = t.get();
            notifyStatusListeners(r.getCode()==0,r.getErrorMsg());
        } catch (InterruptedException e) {
            notifyStatusListeners(false, "interrupted");
            e.printStackTrace();
        } catch (ExecutionException e) {
            notifyStatusListeners(false, "something went wrong");
            e.printStackTrace();
        } 
        
        
    }
    
    public void sendCmd(String s){
        List<String> commands = new LinkedList<String>();
        commands.add(s);        
        send(commands);
    	
    }
    
    private void addPrimitive(String string) throws UnknownComponentTypeException {
		PrimComponentType pc = (PrimComponentType)ComponentTypeRegistry.getInstance().getComponentType("primitive");
		pc.addPrimitiveName(string);
	}
}
