/*
  ==============================================================================

    Delay.h
    Created: 18 Mar 2023 2:45:26pm
    Author:  程

  ==============================================================================
*/

#ifndef Delay_h
#define Delay_h

#include "JuceHeader.h"
#include "AudioHelpers.h"

class Delay {
    
public:
    
    /* */
    Delay();
    
    /* */
    ~Delay();
    
    /* */
    void initialize(float inSampleRate, int inBlocksize);
    
    /* */
    void setParameters(float inTimeSeconds, float inFeedbackAmount, float inMix, float inLPFreq, float inHPFreq);
    
    /* */
    void processBlock(float* inBuffer, int inNumSamples);
    
    /* */
    void processSample(float& inSample);
    
private:
    
    float mSampleRate;
    
    float mMix = 0;
//    float mGain = 0;
    float mFeedbackAmount = 0;
    juce::LinearSmoothedValue<float> mTimeInSeconds;
    
    float mWriteHead = 0;
    float mFeedbackSample = 0;
    juce::AudioBuffer<float> mCircularBuffer;
        
    juce::dsp::IIR::Coefficients<float> mHighpassCoefficients;
    juce::dsp::IIR::Filter<float> mHighPassFilter;
    
    juce::dsp::IIR::Coefficients<float> mLowpassCoefficients;
    juce::dsp::IIR::Filter<float> mLowpassFilter;
};

#endif /* Delay_h */
