//
// Created by 程 on 12/28/23.
//

#ifndef JCPLUGINS_AUDIOFILTERS_H
#define JCPLUGINS_AUDIOFILTERS_H
#include "AudioHelpers.h"
#include "JuceHeader.h"

class AudioFilter
{

public:

    AudioFilter();

    ~AudioFilter();

    void initialize(float inSampleRate, int inBlocksize);

    void setParameters(float inLPFreq, float inHPFreq);

    void processBlock(float* inBuffer, int inNumSamples);

    void processSample(float& inSample);

private:

    float mSampleRate {};
    juce::AudioBuffer<float> mCircularBuffer;
    juce::dsp::IIR::Filter<float> mHighPassFilter;
    juce::dsp::IIR::Filter<float> mLowpassFilter;
};
#endif //JCPLUGINS_AUDIOFILTERS_H
