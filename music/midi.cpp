/**
 * @file midi.cpp
 * @brief  Brief description of file.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <list>
#include <jack/jack.h>
#include <jack/midiport.h>
#include <pthread.h>

#include "midi.h"
#include "util/time.h"

/// all ports must be linked into this.
std::list<class MidiPort *> portList;

static jack_client_t *jack=NULL;
static void chkjack(){
    if(!jack)
        throw "jack not connected";
}

#define DATABUFSIZE 2048

class MidiPort {
public:
    MidiPort(bool input,const char *name){
        isInput = input;
        pthread_mutex_init(&mutex,NULL);
        port = jack_port_register(jack,name,
                                  JACK_DEFAULT_MIDI_TYPE,
                                  isInput?JackPortIsInput:JackPortIsOutput,0);
        if(!port)
            throw "failed to register Jack port";
        portList.push_back(this);
        ct=0;
        rct=0;
    }
    
    ~MidiPort(){
        if(port && jack)
            jack_port_unregister(jack,port);
        portList.remove(this);
        pthread_mutex_destroy(&mutex);
    }
    
    void setListener(MidiPortListener *l){
        listener = l;
    }
    
    // write a single event to the buffer - an event
    // consists of a byte count followed by a number of bytes.
    
    void write(uint8_t *data,int len){
        if(ct+len+1 >= DATABUFSIZE)
            throw "out of space in write buffer";
        pthread_mutex_lock(&mutex);
        dataBuffer[ct++]=len;
        memcpy(dataBuffer+ct,data,len);
        ct+=len;
        pthread_mutex_unlock(&mutex);
    }
    

private:    
    bool isInput;
    jack_port_t *port;
    MidiPort *next;
    pthread_mutex_t mutex;
    
    MidiPortListener *listener;
    
    uint8_t dataBuffer[DATABUFSIZE];
    
    int ct,rct;
    
    
    // returns number of bytes consumed
    int processEvent(uint8_t *d){
        int chan,key,ctor,vel,val;
        uint8_t tp = *d >> 4;
        
        switch(tp){
        case 8:    // noteoff : (chan key vel --)
            chan = *d++ & 0xf;
            key = *d++;
            vel = *d++;
            if(listener)listener->onNoteOff(chan,vel,key);
            // TODO
            break;
        case 9:    // noteon : (chan key vel --)
            chan = *d++ & 0xf;
            key = *d++;
            vel = *d++;
            if(listener)listener->onNoteOn(chan,vel,key);
            // TODO
            break;
        case 11:   // CC : (chan ctor val --)
            chan = *d++ & 0xf;
            ctor = *d++;
            val = *d++;
            if(listener)listener->onCC(chan,ctor,val);
            // TODO
        default:
            break;
        }
        return 3; // jack data is always normalised, it seems
    }

public:    
    // the jack processing callback, called from the jack thread.
    static int process(jack_nframes_t nframes, void *arg){
        std::list<MidiPort *>::iterator i;
        
        // go through each port, see which are output and have data
        // waiting to go, and send it.
        
        for(i=portList.begin();i!=portList.end();++i){
            MidiPort *p = *i;
            void *buf = jack_port_get_buffer(p->port,nframes);
            
            if(p->isInput){
                int ct = jack_midi_get_event_count(buf);
                if(ct>0){
                    pthread_mutex_lock(&p->mutex);
                    uint8_t *data = p->dataBuffer+p->ct;
                    if(p->ct < DATABUFSIZE-3){
                        for(int j=0;j<ct;j++){
                            jack_midi_event_t in;
                            jack_midi_event_get(&in,buf,j);
                            data[0] = in.buffer[0];
                            data[1] = in.buffer[1];
                            data[2] = in.buffer[2];
                            data+=3;
                        }
                    }
                    p->ct = data-p->dataBuffer;
                    pthread_mutex_unlock(&p->mutex);
                }
            }else{
                jack_midi_clear_buffer(buf);
                pthread_mutex_lock(&p->mutex);
                uint8_t *data = p->dataBuffer;
                int idx=0;
                while(idx<p->ct){
                    // run through the data, processing the events
                    int len = data[idx++];
                    jack_midi_event_write(buf,0,data+idx,len);
                    idx+=len;
                }
                p->ct=0;
                pthread_mutex_unlock(&p->mutex);
            }
        }
        return 0;
    }
    
};



static void jack_shutdown(void *arg){
    fprintf(stderr,"Jack terminated the program\n");
    exit(1);
}


MidiPort *midiCreateInput(const char *name){
    chkjack();
    return new MidiPort(true,name);
}
MidiPort *midiCreateOutput(const char *name){
    chkjack();
    return new MidiPort(false,name);
}    

void initMidi(const char *name){
    jack = jack_client_open(name,JackNullOption,NULL);
    if(!jack)
        throw "Jack client open failed";
    jack_on_shutdown(jack,jack_shutdown,0);
    jack_set_process_callback(jack,MidiPort::process,0);
    jack_activate(jack);
}

void shutdownMidi(){
    if(jack){
        jack_deactivate(jack);
        jack_client_close(jack);
        jack=NULL;
    }
}

void sendNoteOn(MidiPort *p,int chan,int note,int vel){
    chkjack();
    
    uint8_t data[3];
    data[0]=144+chan;
    data[1]=note;
    data[2]=vel;
    
    p->write(data,3);
    
}
void sendNoteOff(MidiPort *p,int chan,int note){
    chkjack();
    
    uint8_t data[3];
    data[0]=128+chan;
    data[1]=note;
    data[2]=64;
    
    p->write(data,3);
}
void sendCC(MidiPort *p,int chan,int ctor,int val){
    chkjack();
    
    uint8_t data[3];
    data[0]=(0b10110000)+(chan-1); // channels start at 1?
    data[1]=ctor;
    data[2]=val; 
}




static MidiPort *in,*out;
static float noteEnds[16][128];
void simpleMidiInit(){
    initMidi("stumpymusic");
    in = midiCreateInput("in");
    out = midiCreateOutput("out");
    for(int c=0;c<16;c++){
        for(int i=0;i<128;i++)
            noteEnds[c][i]=-1;
    }
}

void simpleMidiShutdown(){
    for(int c=0;c<16;c++){
        for(int i=0;i<128;i++){
            if(noteEnds[c][i]>=0)
                sendNoteOff(out,c,i);
        }
    }
    sleep(1);
    delete in;
    delete out;
    shutdownMidi();
}

void simpleMidiUpdate(){
    for(int c=0;c<16;c++){
        for(int i=0;i<128;i++){
            if(noteEnds[c][i]>=0){
                if(Time::now() >= noteEnds[c][i]){
                    noteEnds[c][i]=-1;
                    sendNoteOff(out,c,i);
                }
            }
        }
    }
}

void simpleMidiPlay(int chan, int note, int vel,float dur){
//    printf("PLAY %d, %d, vel %d, dur %f\n",
//           chan,note,vel,dur);
    if(chan>=0 && chan<16 && note>=0 && note<128){
        noteEnds[chan][note] = Time::now()+dur;
        sendNoteOn(out,chan,note,vel);
    }
}

