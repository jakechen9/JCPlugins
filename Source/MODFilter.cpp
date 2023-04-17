/*
  ==============================================================================

    MODFilter.cpp
    Created: 16 Apr 2023 4:12:13pm
    Author:  程

  ==============================================================================
*/

#include "MODFilter.h"


MODFilter::MODFilter()
{
    
}

MODFilter::~MODFilter()
{
    
}

void MODFilter::initialize(float inSampleRate, int inBlocksize)
{
    mSampleRate = inSampleRate;
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = inSampleRate;
    spec.maximumBlockSize = inBlocksize;
    spec.numChannels = 1;
    
    mFilter.prepare(spec);
    mFilter.reset();
//    isPrepared = true;
}

void MODFilter::setParameters(float inFrequency, float inResonance)
{
//    mModulator = inModulator;
    mFrequency = inFrequency;
    mResonance = inResonance;
    
}

void MODFilter::processBlock(float* inBuffer, int inNumSamples)
{
    for (int i = 0; i < inNumSamples; i++) {
        processSample(inBuffer[i]);
    }
}

void MODFilter::processSample(float& inSample)
{
    mFilter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
//    float modulatedFreq = mFrequency * mModulator;
//    modulatedFreq = std::fmax(std::fmin(modulatedFreq, 22000.f), 20.f);
    mFilter.setCutoffFrequency(mFrequency);
    mFilter.setResonance(mResonance);
}

void MODFilter::reset()
{
    mFilter.reset();
}
