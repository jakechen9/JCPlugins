//
// Created by 程 on 12/28/23.
//

#include "AudioFilters.h"

AudioFilter::AudioFilter() = default;

AudioFilter::~AudioFilter() = default;

void AudioFilter::initialize(float inSampleRate, int inBlocksize)
{
    mSampleRate = inSampleRate;
    mCircularBuffer.setSize(1, static_cast<int>(5 * inSampleRate));
    juce::dsp::ProcessSpec spec {};
    spec.sampleRate = inSampleRate;
    spec.maximumBlockSize = static_cast<unsigned int>(inBlocksize);
    spec.numChannels = 1;

    mHighPassFilter.prepare(spec);
    mLowpassFilter.prepare(spec);

    mHighPassFilter.reset();
    mLowpassFilter.reset();
}

void AudioFilter::setParameters(float inLPFreq, float inHPFreq)
{
    mLowpassFilter.coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(mSampleRate, inLPFreq);
    mHighPassFilter.coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(mSampleRate, inHPFreq);
}

void AudioFilter::processBlock(float* inBuffer, int inNumSamples)
{
    for (int i = 0; i < inNumSamples; i++) {
        processSample(inBuffer[i]);
    }
}

void AudioFilter::processSample(float& inSample)
{
    float outputSample = inSample;
    outputSample = mLowpassFilter.processSample(outputSample);
    outputSample = mHighPassFilter.processSample(outputSample);
    inSample = outputSample;
}