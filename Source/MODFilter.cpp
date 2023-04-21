/*
  ==============================================================================

    MODFilter.cpp
    Created: 21 Apr 2023 1:20:34pm
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
    mCircularBuffer.setSize(1, 5 * inSampleRate);
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = inSampleRate;
    spec.maximumBlockSize = inBlocksize;
    spec.numChannels = 1;
    
    mFilter.prepare(spec);
    mFilter.reset();
    mCircularBuffer.clear();
}

void MODFilter::setParameters(float inFrequency, float inResonance)
{

    mFilter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
    mFilter.setCutoffFrequency(inFrequency);
    mFilter.setResonance(inResonance);
    
}

void MODFilter::processBlock(float* inBuffer, int inNumSamples)
{
    for (int i = 0; i < inNumSamples; i++) {
        processSample(inBuffer[i]);
    }
}

void MODFilter::processSample(float& inSample)
{
    mWriteHead++;
    if (mWriteHead >= mCircularBuffer.getNumSamples()) {
        mWriteHead = 0;
    }
    float read_head = mWriteHead;
    read_head = AudioHelpers::wrap_buffer(read_head, mCircularBuffer.getNumSamples());
    int sample_x_pos = floor(read_head);
    int sample_x1_pos = sample_x_pos + 1;
    
    sample_x1_pos = AudioHelpers::wrap_buffer(sample_x1_pos, mCircularBuffer.getNumSamples());
    float inter_sample_amount = read_head - sample_x_pos;
    
    float sample_x = mCircularBuffer.getSample(0, sample_x_pos);
    float sample_x1 = mCircularBuffer.getSample(0, sample_x1_pos);
    float output_sample = AudioHelpers::lin_interp(sample_x, sample_x1, inter_sample_amount);
    output_sample = mFilter.processSample(0, output_sample);
//    float modulatedFreq = mFrequency * mModulator;
//    modulatedFreq = std::fmax(std::fmin(modulatedFreq, 22000.f), 20.f);
}

