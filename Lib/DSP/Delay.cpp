/*
  ==============================================================================

    Delay.cpp
    Created: 18 Mar 2023 2:45:26pm
    Author:  程

  ==============================================================================
*/

#include "Delay.h"

/* */
Delay::Delay()
= default;

/* */
Delay::~Delay()
= default;

/* */
void Delay::initialize(float inSampleRate, int inBlocksize)
{
    mSampleRate = inSampleRate;
    mADSR.setSampleRate(inSampleRate);
    mCircularBuffer.setSize(1, static_cast<int>(5 * inSampleRate));
    mTimeInSeconds.reset(inSampleRate, 0.25);
    mTimeInSeconds.setCurrentAndTargetValue(static_cast<float>(0.01));
    mGrainPitch.reset(inSampleRate, .01);
    juce::dsp::ProcessSpec spec{};
    spec.sampleRate = inSampleRate;
    spec.maximumBlockSize = static_cast<unsigned int>(inBlocksize);
    spec.numChannels = 1;
    
    mHighPassFilter.prepare(spec);
    mLowpassFilter.prepare(spec);
    
    mHighPassFilter.reset();
    mLowpassFilter.reset();

    mRealTimeGranulator.prepareToPlay(static_cast<int>(inSampleRate));
}

/* */
void Delay::setParameters(float inTimeSeconds, float inFeedbackAmount, float inMix, float inLPFreq, float inHPFreq, float inGrainPitch, float inAttack,
                          float inDecay, float inSustain, float inRelease, float inNoteLength)
{
    mTimeInSeconds.setTargetValue(inTimeSeconds);
    mFeedbackAmount = inFeedbackAmount;
    mMix = inMix;

    mNoteLength = inNoteLength;
    adsr_param.attack = inAttack;
    adsr_param.decay = inDecay;
    adsr_param.sustain = inSustain;
    adsr_param.release = inRelease;
    mADSR.setParameters(adsr_param);

    mHighPassFilter.coefficients = mHighpassCoefficients.makeHighPass(mSampleRate, inHPFreq);
    mLowpassFilter.coefficients = mLowpassCoefficients.makeLowPass(mSampleRate, inLPFreq);
    mGrainPitch.setTargetValue(inGrainPitch);
}

/* */
void Delay::processBlock(float* inBuffer, int inNumSamples)
{
    for (int i = 0; i < inNumSamples; i++) {
        processSample(inBuffer[i]);
    }
}

/* */
void Delay::processSample(float& inSample)
{
    if (!mADSRStarted) {
        mADSRStarted = true;
        mADSR.noteOn();
    }
    if (static_cast<float>(mCounter) > mNoteLength){
        mADSR.noteOff();
        mCounter = 0;
        mADSR.noteOn();
//        DBG("ADSR Triggered");
    }
    mCounter +=1;
//    DBG(mCounter);
    float ADSRMOD = mADSR.getNextSample();




    mCircularBuffer.setSample(0, static_cast<int>(mWriteHead), std::tanh(inSample + (mFeedbackSample * mFeedbackAmount)));
    
    mWriteHead++;
    
    if (mWriteHead >= static_cast<float>(mCircularBuffer.getNumSamples())) {
        mWriteHead = 0;
    }
    
    float time_in_sample = mTimeInSeconds.getNextValue() * mSampleRate;
    float read_head = mWriteHead - time_in_sample;
    
    read_head = AudioHelpers::wrap_buffer(read_head, static_cast<float>(mCircularBuffer.getNumSamples()));

    int sample_x_pos = static_cast<int>(floor(read_head));
    int sample_x1_pos = sample_x_pos + 1;
    
    sample_x1_pos = static_cast<int>(AudioHelpers::wrap_buffer(static_cast<float>(sample_x1_pos),
                                                               static_cast<float>(mCircularBuffer.getNumSamples())));
    
    float inter_sample_amount = read_head - static_cast<float>(sample_x_pos);

    float sample_x = mCircularBuffer.getSample(0, sample_x_pos);
    float sample_x1 = mCircularBuffer.getSample(0, sample_x1_pos);
    float output_sample = AudioHelpers::lin_interp(sample_x, sample_x1, inter_sample_amount);
        
    output_sample = mHighPassFilter.processSample(output_sample);
    output_sample = mLowpassFilter.processSample(output_sample);
    
    mFeedbackSample = output_sample;
    
    mFeedbackSample = mRealTimeGranulator.processSample(mFeedbackSample, mGrainPitch.getNextValue());
        
    inSample = (output_sample * mMix) + (inSample * (1.f - mMix));

    inSample *= ADSRMOD;
}