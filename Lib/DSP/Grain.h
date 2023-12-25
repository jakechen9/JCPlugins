/*
  ==============================================================================

    Grain.h
    Created: 10 Apr 2023 9:21:05pm
    Author:  程

  ==============================================================================
*/

#ifndef Grain_h
#define Grain_h

#include "JuceHeader.h"
#include "GrainBuffer.h"
#include "AudioHelpers.h"

class Grain {
public:
    
    /* */
    void processSample(const GrainBuffer& inGrainBuffer, float& outLeft, float& outRight) {
        
        float val = getNextWindowSample();
        
        outLeft = inGrainBuffer.getSample(0, static_cast<int>(mGrainReadhead)) * val;
        outRight = inGrainBuffer.getSample(1, static_cast<int>(mGrainReadhead)) * val;
        
        mGrainReadhead += 2.f;
        
        mGrainReadhead = AudioHelpers::wrap_buffer(mGrainReadhead, static_cast<float>(inGrainBuffer.getNumSamples()));
    }

    
    void setSize(int inGrainSize) {
        mGrainSize = inGrainSize;
        // this make it not active after a set size call.
        // could be more explicit
        mGrainCounter = mGrainSize;
    }
//    void setSize(int inGrainSize) {
//        if (mGrainSize != inGrainSize) {
//            mGrainSize = inGrainSize;
//            // this make it not active after a set size call.
//            // could be more explicit
//            mGrainCounter = mGrainSize;
//        }
//    }
        
    void start(float inStartPosition, int inCircularBufferSize, float inGrainPitch) {
        // distance_past_write grain span,
        float distance_past_write = (inGrainPitch - 1.f) * static_cast<float>(mGrainSize);
        mGrainReadhead = inStartPosition;
        mGrainReadhead = AudioHelpers::wrap_buffer(mGrainReadhead - distance_past_write,
                                                   static_cast<float>(inCircularBufferSize));
        mGrainCounter = 0;
    }
    
    float getNextWindowSample() {
        if (isActive()) {
            mGrainCounter++;
                        
            return 0.5f * (1.0f - cos(juce::MathConstants<float>::twoPi * (float)mGrainCounter / (float)mGrainSize));
        } else {
            return 0;
        }
    }
    
    [[nodiscard]] bool isActive() const {
        if (mGrainCounter < mGrainSize) {
            return true;
        } else {
            return false;
        }
    }
    
private:
    
    // where to read from in the buffer
    float mGrainReadhead = 0.f;
    
    // size in sample
    int mGrainSize  = 0;
    
    // position in sample
    int mGrainCounter = 0;
};


#endif /* Grain_h */
