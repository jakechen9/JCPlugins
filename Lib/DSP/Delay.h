/*
  ==============================================================================

    Delay.h
    Created: 18 Mar 2023 2:45:26pm
    Author:  程

  ==============================================================================
*/

#ifndef Delay_h
#define Delay_h

#include "AudioHelpers.h"
#include "JuceHeader.h"
#include "RealTimeGranular.h"

class Delay
{

public:

    /* */
    Delay();

    /* */
    ~Delay();

    /* */
    void initialize(float inSampleRate, int inBlocksize);

    /* */
    void setParameters(float inTimeSeconds,
                       float inFeedbackAmount,
                       float inMix,
                       float inLPFreq,
                       float inHPFreq,
                       float inGrainPitch,
                       float inAttack,
                       float inDecay,
                       float inSustain,
                       float inRelease,
                       float inNoteLength);

    /* */
    void processBlock(float* inBuffer, int inNumSamples);

    /* */
    void processSample(float& inSample);

private:

    RealTimeGranular mRealTimeGranulator;

    float mSampleRate {};
    float mMix = 0;
    float mFeedbackAmount = 0;
    juce::LinearSmoothedValue<float> mTimeInSeconds;
    juce::LinearSmoothedValue<float> mGrainPitch;

    float mWriteHead = 0;
    float mFeedbackSample = 0;
    juce::AudioBuffer<float> mCircularBuffer;
    float mNoteLength = 0;
    float mCounter = 0;
    bool mADSRStarted = false;
    juce::ADSR mADSR;
    juce::ADSR::Parameters adsr_param;
    juce::dsp::IIR::Coefficients<float> mHighpassCoefficients;
    juce::dsp::IIR::Filter<float> mHighPassFilter;

    juce::dsp::IIR::Coefficients<float> mLowpassCoefficients;
    juce::dsp::IIR::Filter<float> mLowpassFilter;
};

#endif /* Delay_h */
