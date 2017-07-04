/**
 * @file chord.cpp
 * @brief  Brief description of file.
 *
 */

#include "model.h"
#include "time.h"
#include "../chordcon.h"
#include "util.h"

#include <math.h>
#include <ctype.h>



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

#include "scaledata.h"



// used my the autochord system, mainly. But handy. Format:
// noteletter[#|b][mode].
// Returns the scale as a ptr to a static array,
// only parsing stuff before the first null/space.

int *parseScale(const char *s){
    static int ret[8];
    
    // first, get the base note.
    if(!isalpha(*s))return NULL;
    
    int bni = tolower(*s++)-'c'; // get basenote based on C, wrap a and b around.
    if(bni>4)return NULL;
    if(bni<0)bni+=7;
    if(bni<0)return NULL;
    
    // get that note's actual MIDI value
    static const int basenotes[] ={24,26,28,29,31,33,35};
    int base = basenotes[bni];
    
    // get any sharp or flat
    if(*s=='#'){s++; base++;}
    else if(*s=='b'){s++; base--;}
    // next three chars should be a mode. If there's a space, then there's no mode (and
    // it's Ionian/Major)
    int mode = 0; // ionian default
    if(*s && isalpha(*s) && s[1] && isalpha(s[1]) && s[2] && isalpha(s[2])){
        char modename[4];
        modename[0]=tolower(s[0]);
        modename[1]=tolower(s[1]);
        modename[2]=tolower(s[2]);
        modename[3]=0;
        const char *chordModes[] = {
            "ion","dor","phr","lyd","mix","aeo","loc",
        };
        if(!strcmp(modename,"min"))mode=5;
        else {
            for(int i=0;i<7;i++){
                if(!strcmp(modename,chordModes[i])){mode=i;break;}
            }
        }
    }
    
    // these are the semitone intervals for major.
    static const int major[] = {2,2,1,2,2,2,1};
    // build the scale from the base using the semitones and the mode.
    int n=base;
    for(int i=0;i<8;i++){
        ret[i]=n;
        n+=major[(i+mode)%7];
    }
    
    return ret;
}

// parse a chord, by getting the scale and then the notes for the chord
// (by default 1,3,5).

int *parseChord(char *s,int *len){
    static int ret[8];
    
    // first get the scale
    
    char *scstr = strtok(s," ");
    int *scale = parseScale(scstr);
    if(!scale)return NULL;
    
    // set up the basic notes as indices into the scale. If -ve, a note is skipped.
    int notes[8];int notect=3;
    notes[0]=0;
    notes[1]=2;
    notes[2]=4;
    // then iterate through space-separated modifiers.
    while(char *s = strtok(NULL," ")){
        if(!strcasecmp(s,"sus2"))notes[1]=1;
        else if(!strcasecmp(s,"all")){
            for(int i=0;i<8;i++){
                notes[i]=i;
            }
            notect=8;break;
        }
        else if(!strcasecmp(s,"sus4"))notes[1]=3;
        else if(!strcasecmp(s,"no3"))notes[1]=-1;
        else if(isdigit(*s))notes[notect++]=(*s-'0')-1;
    }
    
    // construct the chord
    int outct=0;
    for(int i=0;i<notect;i++){
//        printf("%d\n",notes[i]);
        if(notes[i]<8)
            ret[outct++]=scale[notes[i]];
    }
    if(len)*len=outct;
    while(outct<8)
        ret[outct++]=-1;
    
    return ret;
}

static char *noteName(int i){
    static char buf[32];
    static const char *notes[]={"C","C#","D","D#",
        "E","F","F#","G",
        "G#","A","A#","B"};
    sprintf(buf,"%s%d(%d)",notes[(i-24)%12],(i-24)/12,i);
    return buf;
}


// get the centroid of a chord, used for measuring
// inversions
static float getCentre(const BitField& b){
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

/*
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
*/
unsigned char scaleLengths[128]; // at least as many as there are entries in above table.
    
struct ChordData {
    BitField lastChord;
};


class Chord : public ComponentType {
    static const int NUMCHORDS=4;
    StringParameter *pChords[NUMCHORDS];
    IntParameter *pOctave,*pCycles;
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
                  pCycles = new IntParameter("cycles",1,4,1),
                  NULL);
        
        // count notes in each scale
        for(int i=0;scaleData[i][0]>=0;i++){
            int ct;
            for(ct=0;scaleData[i][ct]>=0;ct++){}
//            printf("Scale %d, len %d\n",i,ct);
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
        int cycles= pCycles->get(c);
        
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
                b = construct(base,str,sc,sclen,0,cycles);
            } else {
                int found=0;
                int mindist=10000;
                BitField bs[11];
                for(int i=0;i<11;i++){
                    bs[i] = construct(base,str,sc,sclen,i-5,cycles);
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
            b = construct(base,str,sc,sclen,0,cycles);
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
            bool qqq=false;
            for(int i=0;i<128;i++){
                if(b2.get(i)){
                    printf("%s ",noteName(i));
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
                       const int *scale,int sclen,int inv,int cycles){
        BitField b;
        b.clear();
        int len = strlen(str);
        for(int i=0;i<len*cycles;i++){
            int noteno = (i+inv)+(len*100);
            int octave = noteno/len;
            noteno %= len;
            
            int note;
            char c = str[noteno];
            note = hexdigit(c);
            note = scale[note%sclen];
            note += base+(octave-99)*12;

            if(note>=0 && note<128)
                b.set(note,true);
        }
        return b;
    }
    
};

static Chord chordreg;



// takes 2 chords, pads the shorter one with -1, morphs between them
struct ChordMorpherData {
    int count; // number of notes in padded input sequence
    int *seq1,*seq2;
    BitField chord1,chord2;
    
    void reset(){
        seq1=seq2=NULL;
        chord1.clear();
        chord2.clear();
    }
    void clear(){
        if(seq1)delete [] seq1;
        if(seq2)delete [] seq2;
        seq1=seq2=NULL;
    }
    
    void regenFromChords(int seed,BitField& c1,BitField& c2){
        //  delete old sequence data
        clear();
        
        // count notes in both chords
        int ct1=0,ct2=0;
        for(int i=0;i<128;i++)
            if(c1.get(i))ct1++;
        for(int i=0;i<128;i++)
            if(c2.get(i))ct2++;
        
        // get the biggest; thats the size we'll use
        count = (ct1>ct2) ? ct1:ct2;
        if(!count)return; // blank chords! Can't have that.
        
        // create the arrays and copy the chords into seq1,seq2,
        // padding with -1 if required
        seq1=new int[count];
        seq2=new int[count];
        int n1=0,n2=0;
        for(int i=0;i<128;i++){
            if(c1.get(i))seq1[n1++]=i;
            if(c2.get(i))seq2[n2++]=i;
        }
        for(int i=n1;i<count;i++)seq1[i]=-1;
        for(int i=n2;i<count;i++)seq2[i]=-1;
        
        // and shuffle
        unsigned int rstate = seed;
        shuf<int>(seq1,count,&rstate);
        shuf<int>(seq2,count,&rstate);
    }
    
    void morph(BitField& out,float t){
        // only change the output chord if the inputs are valid
        if(seq1 && seq2){
            int n = (int)(t*(count+1));
            for(int i=0;i<count;i++){
                // get the note to set in the output
                int note = (i>=n)?seq1[i]:seq2[i];
//                printf("Setting note %d to %d (seq%d)\n",i,note,(i>=n)?1:2);
                // set if not -1
                if(note>=0)
                    out.set(note,true);
            }
        } 
    }
};    


class ChordMorpher : public ComponentType {
    static const int NUMCHORDS=8;
    FloatParameter *pAdd,*pMul;
    IntParameter *pSeed;
    
public:
    ChordMorpher() : ComponentType("chordmorpher","music"){}
    virtual void init(){
        width = 170;
        setInput(0,tFloat,"input");
        for(int i=0;i<NUMCHORDS;i++){
            char buf[32];
            sprintf(buf,"in %d",i);
            setInput(i+1,tChord,strdup(buf));
        }
        setOutput(0,tChord,"out");
        addParameter(pMul=new FloatParameter("mul",-100,100,1));
        addParameter(pAdd=new FloatParameter("add",-100,100,0));
        addParameter(pSeed=new IntParameter("seed",0,1000,0));
    }
    virtual void initComponentInstance(ComponentInstance *c){
        ChordMorpherData *d = new ChordMorpherData();
        c->privateData = (void *)d;
    }
    virtual void shutdownComponentInstance(ComponentInstance *c){
        ChordMorpherData *d = (ChordMorpherData *)c->privateData;
        d->clear();
        delete d;
    }
        
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        ChordMorpherData *d = (ChordMorpherData *)ci->privateData;
        float select = tFloat->getInput(ci,0);
        int seed = pSeed->get(c);
        select *= pMul->get(c);
        select += pAdd->get(c);
        
        BitField outchord;
        outchord.clear();
        
        // work out how many inputs are active - chords must be 
        // connected from connection 1 upwards or they are ignored.
        int numins;
        for(numins=0;numins<NUMCHORDS;numins++)
            if(!c->isInputConnected(numins+1))break;
        
        if(numins == 0){
            // none, output a blank chord
        } else if(numins == 1){
            // 1, just copy it from the first
            outchord = tChord->getInput(ci,1);
        } else {
            // work out which chords we are morphing between
            if(select>0.99999)select=0.99999;
            if(select<0)select=0;
            float idx = select*(numins-1);
            int fst=(int)idx;
            BitField c1 = tChord->getInput(ci,fst+1);
            BitField c2 = tChord->getInput(ci,fst+2);
            // and the parameter within the morph
            float t = idx-(float)fst;
            
            
            c->dprintf("Morphing between inputs %d and %d, param %f\n",fst+1,fst+2,t);
            
            d->regenFromChords(seed,c1,c2); // FIX - IS SLOW
            
            d->morph(outchord,t);
                
            
        }
        
        tChord->setOutput(ci,0,outchord);
    }
};   
        
static ChordMorpher cmreg;





// this is more cunning - it generates a whole set of chords (which you may choose to
// wire into a chordmorpher) from strings.
// Chord string format:
//
//

#define ACNUMCHORDS 4

struct ChordDataAC {
    BitField lastChord;
    BitField chord;
    bool done;
};


class AutoChorder : public ComponentType {
    
    StringParameter *pChords[ACNUMCHORDS];
    IntParameter *pOctave,*pCycles;
    BoolParameter *pInversions,*pPrint;
    
public:
    AutoChorder() : ComponentType("autochorder","music"){}
    virtual void init(){
        width = 170;
        
        setParams(pInversions = new BoolParameter("inversions",true),
                  pOctave = new IntParameter("octave",0,5,2),
                  pCycles = new IntParameter("cycles",1,4,1),
                  pPrint = new BoolParameter("print",false),
                  NULL
                  );
        
        for(int i=0;i<ACNUMCHORDS;i++){
            char buf[32];
            sprintf(buf,"chord %d",i);
            char *p=strdup(buf);
            setOutput(i,tChord,p);
            addParameter(pChords[i]=new StringParameter(p,"Cmaj"));
        }
    }
    
    virtual void initComponentInstance(ComponentInstance *c){
        ChordDataAC *d = new ChordDataAC[ACNUMCHORDS];
        c->privateData = (void *)d;
        for(int i=0;i<ACNUMCHORDS;i++){
            d[i].lastChord.clear();
            d[i].done=false;
        }
        
        regenerate(c);
    }
    
    virtual void shutdownComponentInstance(ComponentInstance *c){
        delete []  ((ChordDataAC *)c->privateData);
    }
    
    // given notes in a chord, number of those, an inversion number and the
    // number of cycles to do, get a chord bitfield.
    BitField construct(int *notes,int len,int inv,int cycles){
        BitField b;
        b.clear();
        for(int i=0;i<len*cycles;i++){
            int noteno = (i+inv)+len*100; // inv may be -ve
            int octave = noteno/len-100;
            int note = notes[noteno%len];
            
            //printf("%d: noteno%d->%d, note %d, oct %d\n",i,noteno,noteno%len,note,octave);
            note += octave*12;
            if(note>=0 && note<128)
                b.set(note,true);
        }
        return b;
    }
    
    void regenerate(ComponentInstance *ci){
        Component *c = ci->component;
        ChordDataAC *d = (ChordDataAC *)ci->privateData;
        
        int octave = pOctave->get(c);
        int cycles= pCycles->get(c);
        
        for(int i=0;i<ACNUMCHORDS;i++){
            const char *s = pChords[i]->get(c);
            char chrd[256]; // have to copy, parseChord uses strtok
            strcpy(chrd,s);
            int len;
            int *notes = parseChord(chrd,&len);
            
            BitField b;
            if(pInversions->get(c)){
                float cent = getCentre(d[i].lastChord);
                if(cent<0.01)
                    b = construct(notes,len,0,cycles);
                else {
                    int found = 0;
                    int mindist = 10000;
                    BitField bs[11];
                    for(int i=0;i<11;i++){
                        bs[i] = construct(notes,len,i-5,cycles);
                        float dist = fabsf(getCentre(bs[i])-cent);
                        if(dist<mindist){
                            mindist=dist;
                            found = i;
                        }
                    }
                    b = bs[found];
                }
            } else {
                b = construct(notes,len,0,cycles);
            }
            d[i].lastChord = b;
            d[i].done = true;
            d[i].chord.clear();
            for(int j=0;j<128;j++){
                if(b.get(j)){
                    c->dprintf("Note %d is set in chorder -> %d\n",j,j+12*octave);
                    d[i].chord.set(j+12*octave,true);
                }
            }
        }            
    }
    
    virtual void onParamChanged(ComponentInstance *ci, UNUSED Parameter *p){
        regenerate(ci);
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        ChordDataAC *d = (ChordDataAC *)ci->privateData;
        
        if(!d[0].done)
            regenerate(ci); // just in case
        
        BitField& b = d[out].chord;
        if(pPrint->get(c)){
            bool qqq=false;
            for(int i=0;i<128;i++){
                if(b.get(i)){
                    printf("%s ",noteName(i));
                    qqq=true;
                }
            }
            if(qqq)putchar('\n');
        }
        tChord->setOutput(ci,out,b);
        
        
        
    }
    

};
static AutoChorder acreg;
