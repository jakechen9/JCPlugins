/*
  ==============================================================================

    RealTimeGranular.cpp
    Created: 10 Apr 2023 9:21:55pm
    Author:  程

  ==============================================================================
*/

#include "RealTimeGranular.h"

/* */
void RealTimeGranular::prepareToPlay(int inSampleRate)
{
    mSampleRate = static_cast<float>(inSampleRate);
    for (auto& mGrain : mGrains) {
        mGrain.setSize(mGrainsizeSeconds * mSampleRate);
    }

    mGrainBuffer.setSize(static_cast<int>(10.f * static_cast<float>(inSampleRate)));
    mScheduler.setTime(mGrainsizeSeconds / mGrainOverlapRate * static_cast<float>(inSampleRate));
    mScheduler.reset();
}

/* */
float RealTimeGranular::processSample(float inSample, float inGrainPitch, float inGrainSize)
{
    mGrainsizeSeconds = inGrainSize;
    mGrainBuffer.writeToBuffer(inSample, inSample);

    if (mScheduler.trigger()) {
        for (auto& mGrain : mGrains) {
            if (!mGrain.isActive()) {
                mGrain.start(
                    static_cast<float>(mGrainBuffer.getWriteHead() - 2), mGrainBuffer.getNumSamples(), inGrainPitch);
                break;
            }
        }
    }

    inSample = 0;

    float temp_left;
    float temp_right;

    for (auto& mGrain : mGrains) {
        if (mGrain.isActive()) {
            mGrain.processSample(mGrainBuffer, temp_left, temp_right);
            inSample += temp_left;
        }
    }

    return inSample;
}
