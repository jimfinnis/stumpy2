/**
 * @file globals.h
 * @brief  Brief description of file.
 *
 */

#ifndef __GLOBALS_H
#define __GLOBALS_H

#include "bitfield.h"

// global tempo
extern float gTempo;    
// global velocity multiplier
extern float gVel;
// global transposition
extern int gTrans;

// if all notes enforced to the same octave (based on C) this is it.
// This is done at a very low level in the actual midi out code!
// -100 if not enforced.
extern int gEnforcedOct;

// this makes gEnforcedOct a bit redundant. It specifies a range
// of octaves we should be in; by default both -100 (unlimited)

extern int gMinOct,gMaxOct;

// debug midi, there's a component for this.
extern bool gDebugMidi;


// the current "chord as state" - the chord used by single-chord-input 
// components whose chord input is not wired up.
extern BitField gChord;

#endif /* __GLOBALS_H */
