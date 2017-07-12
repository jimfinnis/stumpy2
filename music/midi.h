/**
 * @file midi.h
 * @brief  Brief description of file.
 *
 */

#ifndef __MIDI_H
#define __MIDI_H
class MidiPort;

class MidiPortListener {
public:
    virtual void onNoteOn(int chan,int vel,int key)=0;
    virtual void onNoteOff(int chan,int vel,int key)=0;
    virtual void onCC(int chan,int vel,int key)=0;
};

MidiPort *midiCreateInput(const char *name);
MidiPort *midiCreateOutput(const char *name);

void initMidi();
void shutdownMidi();

void sendNoteOn(MidiPort *p,int chan,int note,int vel);
void sendNoteOff(MidiPort *p,int chan,int note);
void sendCC(MidiPort *p,int chan,int ctor,int val);

void simpleMidiInit(MidiPortListener *l);
void simpleMidiShutdown();
void simpleMidiUpdate();
void simpleMidiPlay(int chan, int note, int vel,float dur,bool suppressRetrig);
void simpleMidiCC(int chan, int ctor,int val);

#endif /* __MIDI_H */
