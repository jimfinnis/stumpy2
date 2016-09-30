/**
 * @file globals.h
 * @brief  Brief description of file.
 *
 */

#ifndef __GLOBALS_H
#define __GLOBALS_H

// global tempo
extern float gTempo;    
// global velocity multiplier
extern float gVel;
// global transposition
extern int gTrans;
// if all notes enforced to the same octave (based on C) this is it.
// This is done at a very low level in the actual midi out code!
// -ve if not enforced.
extern int gEnforcedOct;
#endif /* __GLOBALS_H */
