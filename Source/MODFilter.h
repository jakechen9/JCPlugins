/*
  ==============================================================================

    MODFilter.h
    Created: 16 Apr 2023 4:12:13pm
    Author:  程

  ==============================================================================
*/

#ifndef MODFilter_h
#define MODFilter_h

#include "JuceHeader.h"

class MODFilter
{
public:
    
    MODFilter();
    
    ~MODFilter();
    
    void initialize(float inSampleRate, int inBlocksize);
    
    void setParameters(float inFrequency, float inResonance);
    
    void processBlock(float* inBuffer, int inNumSamples);
    
    void processSample(float& inSample);
    
    void reset();
    
private:
    float mSampleRate;
    float mModulator = 0;
    float mFrequency = 0;
    float mResonance = 0;
    juce::dsp::StateVariableTPTFilter<float> mFilter;
//    bool isPrepared { false };
};

# endif
