/*
  ==============================================================================

    RealTimeGranular.cpp
    Created: 10 Apr 2023 9:21:55pm
    Author:  程

  ==============================================================================
*/

#include "RealTimeGranular.h"

/* */
void RealTimeGranular::prepareToPlay(int inSampleRate, int inBlockSize)
{
    mSampleRate = inSampleRate;
    for (int i = 0; i < mGrains.size(); i++) {
        mGrains[i].setSize(mGrainsizeSeconds * mSampleRate);
    }
    
    mGrainBuffer.setSize(10.f * inSampleRate);
    mScheduler.setTime(mGrainsizeSeconds / mGrainOverlapRate * inSampleRate);
//    mScheduler.initialize(inSampleRate);
    mScheduler.reset();
    
}



//void RealTimeGranular::setParameters(float inGrainSize)
//{
//    for (int i = 0; i < mGrains.size(); i++) {
//        mGrains[i].setSize(inGrainSize * mSampleRate);
//    }
//    mScheduler.setTime(inGrainSize);
//}


/* */
float RealTimeGranular::processSample(float inSample, float inGrainPitch)
{
    mGrainBuffer.writeToBuffer(inSample, inSample);
    
    
    if (mScheduler.trigger()) {
        for (int j = 0; j < mGrains.size(); j++) {
            if (mGrains[j].isActive() == false) {
                mGrains[j].start(mGrainBuffer.getWriteHead() - 2,
                                 mGrainBuffer.getNumSamples(),
                                 inGrainPitch);
                break;
            }
        }
    }

    inSample = 0;
    
    float temp_left;
    float temp_right;
    
    for (int j = 0; j < mGrains.size(); j++) {
        if (mGrains[j].isActive()) {
            mGrains[j].processSample(mGrainBuffer, temp_left, temp_right);
            inSample += temp_left;
        }
    }
    
    return inSample;
}
