/*
  ==============================================================================

    Filter.h
    Created: 7 Apr 2023 4:25:16pm
    Author:  程

  ==============================================================================
*/

#ifndef Filter_h
#define Filter_h

#include "JuceHeader.h"
#include "AudioHelpers.h"

class Filter {
public:
    
    Filter();
    
    ~Filter();
    
    void initialize(float inSampleRate, int inBlocksize);
    
    void setParameters(float inMix, float inLPFreq, float inHPFreq);
    
    void processBlock(float* inBuffer, int inNumSamples);
    
    void processSample(float& inSample);
    
private:
    float mSampleRate;
    float mWriteHead = 0;
    float mFilterMix = 0;
    juce::AudioBuffer<float> mCircularBuffer;
    juce::dsp::IIR::Coefficients<float> mHighpassCoefficients;
    juce::dsp::IIR::Filter<float> mHighPassFilter;
    
    juce::dsp::IIR::Coefficients<float> mLowpassCoefficients;
    juce::dsp::IIR::Filter<float> mLowpassFilter;
};

# endif



