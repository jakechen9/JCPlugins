/*
  ==============================================================================

    Grain.cpp
    Created: 4 Apr 2023 2:39:32pm
    Author:  程

  ==============================================================================
*/

#include "Grain.h"
Grain::Grain()
{

}

Grain::~Grain()
{

}

void Grain::initialize(float inSampleRate, int inBlocksize)
{
    mSampleRate = inSampleRate;
    mGrainSize = .5f * inSampleRate;
    mGrainCounter = 0;

}

//void Grain::setParameters(float inMix, int inGrainSize)
//{
//    mGrainMix = inMix;
////    mGrainSize = inGrainSize;
//}

void Grain::processBlock(float* inBuffer, int inNumSamples)
{
    for (int i = 0; i < inNumSamples; i++) {
        processSample(inBuffer[i]);
    }
}

void Grain::processSample(float& inSample)
{
    mGrainCounter++;
    auto grain_val = 0.5 * (1 - std::cos(6.283185307179586 * (float)mGrainCounter / (((float)mGrainSize)-1.f)));
    inSample = inSample * grain_val;
    
    if (mGrainCounter > mGrainSize){
        mGrainCounter = 0;
    }
    
//    inSample = (output_sample * mGrainMix) + (inSample * (1.f - mGrainMix));
}
