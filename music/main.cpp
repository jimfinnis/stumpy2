/**
 * @file test.cpp
 * @brief  Brief description of file.
 *
 */

#include <unistd.h>

#include "model.h"
#include "controller.h"
#include "server.h"
#include <diamondapparatus/diamondapparatus.h>

#include "chordcon.h"
#include "midi.h"
#include "util/time.h"

ChordCon *tChord;

int main(int argc,char *argv[]){
    
    simpleMidiInit();
    // create (and register) new connection types
    tChord = new ChordCon();
    
    
    try {
        diamondapparatus::init();
    } catch(diamondapparatus::DiamondException e){
        printf("Diamond initialisation problem : %s\n",e.what());
        exit(1);
    }
    
    Time::init();
    try {
        Server server(65111);
        PatchLibrary lib;
        
        server.setListener(new Controller(&lib,&server));
        for(;;){
            if(!server.process())break;
            lib.run();
            Time::tick();
            usleep(1000);
            simpleMidiUpdate();
        }
    } catch(int x) {
        simpleMidiShutdown();
        printf("Error: %s\n",errorStrings[x]);
        exit(1);
    }
    
    diamondapparatus::destroy();
    simpleMidiShutdown();
}
