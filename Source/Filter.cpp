/*
  ==============================================================================

    Filter.cpp
    Created: 7 Apr 2023 4:25:16pm
    Author:  程

  ==============================================================================
*/

#include "Filter.h"

/* */
Filter::Filter()
{
    
}

/* */
Filter::~Filter()
{
    
}

void Filter::initialize(float inSampleRate, int inBlocksize)
{
    mSampleRate = inSampleRate;
    mCircularBuffer.setSize(1, 5 * inSampleRate);
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = inSampleRate;
    spec.maximumBlockSize = inBlocksize;
    spec.numChannels = 1;
    
    mHighPassFilter.prepare(spec);
    mLowpassFilter.prepare(spec);
    
    mHighPassFilter.reset();
    mLowpassFilter.reset();
    
    mCircularBuffer.clear();
}

void Filter::setParameters(float inMix, float inLPFreq, float inHPFreq)
{
    mFilterMix = inMix;
    
    mHighPassFilter.coefficients = mHighpassCoefficients.makeHighPass(mSampleRate, inHPFreq);
    mLowpassFilter.coefficients = mLowpassCoefficients.makeLowPass(mSampleRate, inLPFreq);
}

void Filter::processBlock(float* inBuffer, int inNumSamples)
{
    for (int i = 0; i < inNumSamples; i++) {
        processSample(inBuffer[i]);
    }
}

void Filter::processSample(float& inSample)
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
    output_sample = mHighPassFilter.processSample(output_sample);
    output_sample = mLowpassFilter.processSample(output_sample);
    inSample = (output_sample * mFilterMix) + (inSample * (1.f - mFilterMix));
}
