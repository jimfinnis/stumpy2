/**
 * @file chord.cpp
 * @brief  Brief description of file.
 *
 */

#include "model.h"
#include "time.h"
#include "../chordcon.h"

#include <math.h>

// takes a root note, generates a chord (bitfield) from it
// by selecting a set of (diatonic) intervals from it, into
// a scale specified from an enum.
// The intervals are specified by a string. A number of 
// strings are provided, which are selected by passing in
// a float (normally zero, the default string). Different
// parts of the float range select different strings.
// If two strings are active (inactive strings are zero length),
// 0-0.5 would select the default, 0.5..-1 would select the other.
//
// If inversions are active, an attempt is made to use inversions
// to keep the next chord as close to the previous one as possible
// (as measured by the distance of the centroids of the chords).
//
// There is also an octave setting.

// a triad.
#define DEFCHORD "024" 

static const char *scaleNames[]= {
    "major",
    "minor",
    "chromatic",
    "pentatonic",
    NULL
};

static const int scaleData[][20]=
{
    {0,2,4,5,7,9,11,-1},
    {0,2,3,5,7,8,11,-1},
    {0,1,2,3,4,5,6,7,8,9,10,11,-1},
    {0,2,4,7,9,-1},
    
    {-1} // terminator
};
unsigned char scaleLengths[64]; // at least as many as there are entries in above table.
    
struct ChordData {
    BitField lastChord;
};


class Chord : public ComponentType {
    static const int NUMCHORDS=4;
    StringParameter *pChords[NUMCHORDS];
    IntParameter *pOctave;
    BoolParameter *pInversions,*pPrint;
    EnumParameter *pScale;
    
public:
    Chord() : ComponentType("chord","music"){}
    virtual void init(){
        setInput(0,tFloat,"base");
        setInput(1,tFloat,"select");
        setOutput(0,tChord,"chord");
        setParams(
                  pChords[0]=new StringParameter("default chord",DEFCHORD),
                  pChords[1]=new StringParameter("chord 1",DEFCHORD),
                  pChords[2]=new StringParameter("chord 2",DEFCHORD),
                  pChords[3]=new StringParameter("chord 3",DEFCHORD),
                  pOctave = new IntParameter("octave",0,5,2),
                  pInversions = new BoolParameter("inversions",true),
                  pPrint = new BoolParameter("print",false),
                  pScale = new EnumParameter("scale",scaleNames,0),
                  NULL);
        
        // count notes in each scale
        for(int i=0;scaleData[i][0]>=0;i++){
            int ct;
            for(ct=0;scaleData[i][ct]>=0;ct++){}
            printf("Scale %d, len %d\n",i,ct);
            scaleLengths[i]=ct;
        }
    }
    
    virtual void initComponentInstance(ComponentInstance *c){
        ChordData *d = new ChordData();
        c->privateData = (void *)d;
        d->lastChord.clear();
    }
    
    virtual void shutdownComponentInstance(ComponentInstance *c){
        delete ((ChordData *)c->privateData);
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        ChordData *d = (ChordData *)ci->privateData;
        
        int base = (int)tFloat->getInput(ci,0);
        float select = tFloat->getInput(ci,1);
              
        int octave = pOctave->get(c)+2;
        
        // select the active chord (input mod numchords)
        int isel = select;
        while(isel<0)
            isel += NUMCHORDS*100;
        isel %= NUMCHORDS;
        const char *str = pChords[isel]->get(c);
        if(!*str)return; // empty
        
        // construct the chord
        
        const int *sc = scaleData[pScale->get(c)];
        int sclen = scaleLengths[pScale->get(c)];
        BitField b;
        if(pInversions->get(c)){
            // here, we have to scan through the inversions
            // until we find a close one.
            float cent = getCentre(d->lastChord);
            if(cent<0.01){
                // no last cord
                b = construct(base,str,sc,sclen,0);
            } else {
                int found=0;
                int mindist=10000;
                BitField bs[11];
                for(int i=0;i<11;i++){
                    bs[i] = construct(base,str,sc,sclen,i-5);
                    float dist = fabsf(getCentre(bs[i])-cent);
                    if(dist<mindist){
                        mindist=dist;
                        found = i;
                    }
                }
                b = bs[found];
            }
        } else {
            // the easy way!
            b = construct(base,str,sc,sclen,0);
        }
        
        
        d->lastChord = b;
        
        BitField b2;
        b2.clear();
        for(int i=0;i<128;i++){
            if(b.get(i))
                b2.set(i+12*octave,true);
        }
        
        tChord->setOutput(ci,0,b2);
        
        
        
        if(pPrint->get(c)){
            static const char *notes[]={"C","C#","D","D#",
                                      "E","F","F#","G",
                                      "G#","A","A#","B"};
            bool qqq=false;
            for(int i=24;i<128;i++){
                if(b2.get(i)){
                    printf("%s%d(%d) ",notes[(i-24)%12],(i-24)/12,i);
                    qqq=true;
                }
            }
            if(qqq)putchar('\n');
        }
        
    }
private:
    
    // construct a chord on a root note, given the inversion
    // (as a number where 0 is first, e.g. 
    //   C1E1G1 (0) -> C1E1G1
    //          (1) -> E1G1C2
    //          (2) -> G1C2E2
    //         (-1) -> G0C1E1
    //         (-1) -> E0G0C1
    // The string is a string of offsets into the scale table,
    // e.g. "024" into major i.e. {0,2,4,5,7,9,11}, gives
    // the chromatic notes 0,4,7 (i.e. a major triad)
    
    BitField construct(int base, const char *str, 
                       const int *scale,int sclen,int inv){
        BitField b;
        b.clear();
        int len = strlen(str);
        for(int i=0;i<len;i++){
            int noteno = (i+inv)+(len*100);
            int octave = noteno/len;
            noteno %= len;
            
            int note;
            char c = str[noteno];
            if(c>='a') 
                // allow hex digits (might be using mad scales)
                note = (c - 'a')+10; 
            else
                note = c-'0';
            note = scale[note%sclen];
            note += base+(octave-99)*12;

            if(note>=0 && note<128)
                b.set(note,true);
        }
        return b;
    }
    
    // get the centroid of a chord, used for measuring
    // inversions
    float getCentre(const BitField& b){
        float t=0;
        int ct=0;
        for(int i=0;i<128;i++){
            if(b.get(i)){
                t+=i; ct++;
            }
        }
        if(ct)
            return t/(float)ct;
        else return 0;
    }
};

static Chord chordreg;

