/*
  ==============================================================================

    RealTimeGranular.h
    Created: 10 Apr 2023 9:21:55pm
    Author:  程

  ==============================================================================
*/
#ifndef RealTimeGranular_h
#define RealTimeGranular_h

#include "Grain.h"
#include "GrainBuffer.h"
#include "Scheduler.h"


class RealTimeGranular {

public:
    
    /* */
    void prepareToPlay(int inSampleRate);
    
    
//    void setParameters(float inGrainSize);
    
    /* */
    float processSample(float inSample, float inGrainPitch);
    
private:
    
    const float mGrainsizeSeconds = 0.1f;
    const float mGrainOverlapRate = 2.f;
    float mSampleRate = 0.f;
    
    
    Scheduler mScheduler;
    GrainBuffer mGrainBuffer;
    std::array<Grain, 10> mGrains;
};

#endif /* RealTimeGranular_h */
