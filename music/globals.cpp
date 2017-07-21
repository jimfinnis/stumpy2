/**
 * @file globals.cpp
 * @brief  Brief description of file.
 *
 */

#include "bitfield.h"

float gTempo=100.0f;
float gVel=1.0f;
int gTrans=0;
int gEnforcedOct=-100;
BitField gChord;
bool gDebugMidi = false;

// init those globals which can't be constructed
void initGlobals(){
    gChord.clear();
    // bung in dummy chord - C Major.
    gChord.set(36,true);
    gChord.set(40,true);
    gChord.set(43,true);
}
