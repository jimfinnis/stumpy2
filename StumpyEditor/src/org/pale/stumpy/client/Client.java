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

import org.pale.stumpy.Configuration;
import org.pale.stumpy.main.TopController;
import org.pale.stumpy.model.ProtocolException;
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
			/// send command to fetch component data etc.
			try {
				Configuration.readConfiguration(INSTANCE);
			} catch (UnknownComponentTypeException e) {
				notifyStatusListeners(false, "couldn't find the primitive component type");
				destroy();
			} catch (IOException e) {
				notifyStatusListeners(false, "IOException occurred in setup");
				destroy();
			} catch (ProtocolException e) {
				notifyStatusListeners(false, "ProtocolException occurred in setup: "+e.getError());
				destroy();
			}
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
		public int code;
		public String status;

		CommsResult(int code,String msg){
			this.code=code;
			status=msg;
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
			return status;
		}
	}

	public void doSend(String cmd) throws IOException{
		System.out.println("sending "+cmd);
		outBuf.clear();
		outBuf.put(cmd.getBytes());
		outBuf.put((byte) 0); // terminate!
		outBuf.flip();
		while(outBuf.hasRemaining())
			socket.write(outBuf); // non blocking, but the loop will deal with it.

	}

	/**
	 * This is used in a blocking style for stateful conversations,
	 * typically getting the initial setup data from the server. 
	 * @return
	 */
	public CommsResult syncRead() {
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
					//System.out.println("Read: "+inBuf.toString());

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
					return new CommsResult(code,bits[1]);
				} catch (IOException e) {
					return new CommsResult(503,"IO exception in read");
				}
			}
		}
		return new CommsResult(510,"timeout");
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

		// Important - if you want to do some chat with the server in here,
		// don't. Use something like the readConfiguration() above.
		// Remember, the CommsTask doesn't exit until all commands
		// have been used up OR the return code is an error (and we return nonerror
		// [0] for the 400+ series).

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
							//System.out.println("Read: "+inBuf.toString());

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

							// this might some some weird 400+ code, which isn't
							// an error per se, but shouldn't arrive here.
							return new CommsResult(code,bits[1]);

						} catch (IOException e) {
							return new CommsResult(503,"IO exception in read");
						}
					}
				}
			}
		}



		@Override
		protected CommsResult doInBackground() throws Exception {
			CommsResult r=new CommsResult(502,"return never processed");

			for(String cmd: commands){
				doSend(cmd);
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
	 * another error occurred, deal. Will use a swing worker, heaven knows why
	 * because it immediately blocks. 
	 * @param s
	 */
	public void sendAndProcessResponse(List<String> commands){
		CommsResult r = new CommsResult(510,"no processing occurred");
		if(!isConnected()){
			r = new CommsResult(520,"not connected!");
			return;
		}
		CommsTask t = new CommsTask(commands);
		r = new CommsResult(510,"no processing occurred");
		try {
			System.out.println("Command batch:::::::::::::::::::::::");
			for(String c: commands){
				System.out.println("---- "+c);
			}
			t.execute();
			r = t.get();
			System.out.println(r);
			notifyStatusListeners(r.getCode()==0,r.getErrorMsg());
		} catch (InterruptedException e) {
			notifyStatusListeners(false, "interrupted");
			e.printStackTrace();
		} catch (ExecutionException e) {
			notifyStatusListeners(false, "something went wrong");
			e.printStackTrace();
		} 


	}

	public void sendCmdAndProcessResponse(String s){
		List<String> commands = new LinkedList<String>();
		commands.add(s);        
		sendAndProcessResponse(commands);

	}

}
