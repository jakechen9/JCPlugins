/*
  ==============================================================================

    Grain.h
    Created: 4 Apr 2023 2:39:32pm
    Author:  程

  ==============================================================================
*/

#ifndef Grain_h
#define Grain_h

#include "JuceHeader.h"


class Grain {
    
public:
    
    Grain();
    
    ~Grain();
    
    void initialize(float inSampleRate, int inBlocksize);
    
//    void setParameters(float inMix, int inGrainSize);
    
    void processBlock(float* inBuffer, int inNumSamples);
    
    void processSample(float& inSample);
    
private:
    float mSampleRate;
    float mGrainMix = 0;
    int mGrainSize = 0;
    int mGrainCounter = 0;
    float mWriteHead = 0;
};

#endif /* Grain_h */
