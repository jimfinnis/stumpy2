/**
 * @file test.cpp
 * @brief  Brief description of file.
 *
 */

#include <unistd.h>

#include "model.h"
#include "controller.h"
#include "server.h"

#include "chordcon.h"
#include "midi.h"
#include "util/time.h"

ChordCon *tChord;

bool midirecvd=false;
class MidiListener : public MidiPortListener {
public:
    virtual void onNoteOn(int chan,int vel,int key){
        midirecvd=true;
    }
    virtual void onNoteOff(int chan,int vel,int key){}
    virtual void onCC(int chan,int vel,int key){}
};

int main(int argc,char *argv[]){
    
    MidiListener midiListener;
    
    simpleMidiInit(&midiListener);
    // create (and register) new connection types
    tChord = new ChordCon();
    
    
    // crude command line parsing
    
    char *filename=NULL;
    bool midisync=false;
    for(int i=1;i<argc;i++){
        char *s = argv[i];
        if(*s=='-'){
            switch(s[1]){
                // -s : wait for a midi noteon on any channel before starting music
            case 's':midisync = true;break;
            default:
                printf("usage: music [-s] [file.pls]\n");
            }
        }else filename = s;
    }
    
    
    Time::init();
    try {
        Server server(65111);
        PatchLibrary lib;
        
        if(filename)
            lib.readFile(filename);
        
        server.setListener(new Controller(&lib,&server));
        
        if(midisync)Time::pause();
        
        for(;;){
            if(!server.process())break;
            lib.run();
            Time::tick();
            usleep(1000);
            simpleMidiUpdate();
            if(midirecvd){
                printf("Note received, syncing\n");
                Time::restart();
                midirecvd=false;
            }
        }
    } catch(int x) {
        simpleMidiShutdown();
        printf("Error: %s\n",errorStrings[x]);
        exit(1);
    }
    
    simpleMidiShutdown();
}
