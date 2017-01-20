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

int main(int argc,char *argv[]){
    
    simpleMidiInit();
    // create (and register) new connection types
    tChord = new ChordCon();
    
    
    Time::init();
    try {
        Server server(65111);
        PatchLibrary lib;
        
        if(argc>1)
            lib.readFile(argv[1]);
        
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
    
    simpleMidiShutdown();
}
