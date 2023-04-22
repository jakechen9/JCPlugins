/*
  ==============================================================================

    MODFilter.h
    Created: 21 Apr 2023 1:20:34pm
    Author:  程

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "AudioHelpers.h"

class MODFilter
{
public:
    
    MODFilter();
    
    ~MODFilter();
    
    void initialize(float inSampleRate, int inBlocksize);
    
    void setParameters(float inFrequency, float inResonance);
    
    void processBlock(float* inBuffer, int inNumSamples);
    
    void processSample(float& inSample);
    
private:
    
    juce::dsp::StateVariableTPTFilter<float> mFilter;
    juce::AudioBuffer<float> mCircularBuffer;
    
    float mWriteHead = 0;
    float mFrequency = 0;
    float mResonance = 0;
    float mSampleRate;
};

