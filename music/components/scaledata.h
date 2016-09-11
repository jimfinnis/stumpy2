/**
 * @file scaledata.h
 * @brief  Brief description of file.
 *
 */

#ifndef __SCALEDATA_H
#define __SCALEDATA_H

static const char *scaleNames[]= {
    "Enigmatic",
    "Ethiopian",
    "Major",
    "Chinese2",
    "MelodicMinor",
    "LydianAugmented",
    "Dorian",
    "LydianMinor",
    "Symmetrical",
    "LeadingWholeTone",
    "LocrianUltra",
    "Chahargah",
    "Spanish8Tone",
    "Arabian",
    "LocrianNatural",
    "Augmented",
    "Chinese1",
    "Algerian1",
    "Lydian",
    "Mongolian",
    "Japanese",
    "HarmonicMajor",
    "Pd",
    "Balinese",
    "Chromatic",
    "Romanian",
    "Todi",
    "MixolydianAugmented",
    "PentatonicMajor",
    "Altered",
    "LocrianMajor",
    "NeapolitanMinor",
    "Pelog",
    "LydianDominant",
    "Byzantine",
    "Blues",
    "HungarianMajor",
    "Kumoi",
    "HungarianGypsy",
    "Algerian",
    "Gypsy",
    "Pa",
    "Egyptian",
    "NaturalMajor",
    "Mixolydian",
    "LocrianSuper",
    "Hindu",
    "Mohammedan",
    "Locrian",
    "Pfcg",
    "Minor",
    "Aeolian",
    "Overtone",
    "NeapolitanMajor",
    "Phrygian",
    "Algerian2",
    "InvertedDiminished",
    "Spanish",
    "BebopDominant",
    "Pe",
    "HarmonicMinor",
    "Diminished",
    "WholeTone",
    "BebopDominantFlatNine",
    "Indian",
    "Chinese",
    "Javanese",
    "BebopMinor",
    "HungarianMinor",
    "Flamenco",
    "PentatonicMinor",
    "NaturalMinor",
    "Iwato",
    "Marva",
    "Persian",
    "PhrygianMajor",
    "BebopMajor",
    "DoubleHarmonic",
    "Pb",
    "Oriental",
    "BebopTonicMinor",
    "Ionian",
    "Hirajoshi",
    "Jewish",
    NULL
};

static const int scaleData[][20]=
{
    {0,1,4,6,8,10,11,12,-1},
    {0,2,4,5,7,8,11,12,-1},
    {0,2,4,5,7,9,11,12,-1},
    {0,4,6,7,11,12,-1},
    {0,2,3,5,7,9,11,12,-1},
    {0,2,4,6,8,9,10,12,-1},
    {0,2,3,5,7,9,10,12,-1},
    {0,2,4,6,7,8,10,12,-1},
    {0,1,3,4,6,7,9,10,12,-1},
    {0,2,4,6,8,10,11,12,-1},
    {0,1,3,4,6,8,9,12,-1},
    {0,1,4,5,7,8,11,12,-1},
    {0,1,3,4,5,6,8,10,12,-1},
    {0,1,4,5,7,8,11,12,-1},
    {0,2,3,5,6,8,10,12,-1},
    {0,3,4,7,8,11,12,-1},
    {0,2,4,7,9,12,-1},
    {0,2,3,6,7,8,11,12,-1},
    {0,2,4,6,7,9,11,12,-1},
    {0,2,4,7,9,12,-1},
    {0,1,5,7,8,12,-1},
    {0,2,4,5,8,9,11,12,-1},
    {0,2,3,7,9,12,-1},
    {0,1,3,7,8,12,-1},
    {0,1,2,3,4,5,6,7,8,9,10,11,12,-1},
    {0,2,3,6,7,9,10,12,-1},
    {0,1,3,6,7,8,11,12,-1},
    {0,2,4,5,8,9,10,12,-1},
    {0,2,4,7,9,12,-1},
    {0,1,3,4,6,8,10,12,-1},
    {0,2,4,5,6,8,10,12,-1},
    {0,1,3,5,7,8,11,12,-1},
    {0,1,3,7,10,12,-1},
    {0,2,4,6,7,9,10,12,-1},
    {0,1,4,5,7,8,11,12,-1},
    {0,3,5,6,7,10,12,-1},
    {0,3,4,6,7,9,10,12,-1},
    {0,1,5,7,8,12,-1},
    {0,2,3,6,7,8,11,12,-1},
    {0,2,3,6,7,8,11,12,-1},
    {0,1,4,5,7,8,11,12,-1},
    {0,2,3,7,8,12,-1},
    {0,2,3,6,7,8,11,12,-1},
    {0,2,4,5,7,9,11,12,-1},
    {0,2,4,5,7,9,10,12,-1},
    {0,1,3,4,6,8,10,12,-1},
    {0,2,4,5,7,8,10,12,-1},
    {0,2,3,5,7,8,11,12,-1},
    {0,1,3,5,6,8,10,12,-1},
    {0,2,4,7,9,12,-1},
    {0,2,3,5,7,8,10,12,-1},
    {0,2,3,5,7,8,10,12,-1},
    {0,2,4,6,7,9,10,12,-1},
    {0,1,3,5,7,9,11,12,-1},
    {0,1,3,5,7,8,10,12,-1},
    {0,2,3,5,7,8,10,12,-1},
    {0,1,3,4,6,7,9,10,12,-1},
    {0,1,4,5,7,8,10,12,-1},
    {0,2,4,5,7,9,10,11,12,-1},
    {0,1,3,7,8,12,-1},
    {0,2,3,5,7,8,11,12,-1},
    {0,2,3,5,6,8,9,11,12,-1},
    {0,2,4,6,8,10,12,-1},
    {0,1,4,5,7,9,10,11,12,-1},
    {0,1,3,4,7,8,10,12,-1},
    {0,2,4,7,9,12,-1},
    {0,1,3,5,7,9,10,12,-1},
    {0,2,3,5,7,8,9,10,12,-1},
    {0,2,3,6,7,8,11,12,-1},
    {0,1,3,4,5,7,8,10,12,-1},
    {0,3,5,7,10,12,-1},
    {0,2,3,5,7,8,10,12,-1},
    {0,1,5,6,10,12,-1},
    {0,1,4,6,7,9,11,12,-1},
    {0,1,4,5,6,8,11,12,-1},
    {0,1,4,5,7,8,10,12,-1},
    {0,2,4,5,7,8,9,11,12,-1},
    {0,1,4,5,7,8,11,12,-1},
    {0,1,3,6,8,12,-1},
    {0,1,4,5,6,9,10,12,-1},
    {0,2,3,5,7,8,9,11,12,-1},
    {0,2,4,5,7,9,11,12,-1},
    {0,2,3,7,8,12,-1},
    {0,1,4,5,7,8,10,12,-1},
    {-1}};


#endif /* __SCALEDATA_H */
