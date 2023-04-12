/*
  ==============================================================================

    GrainBuffer.h
    Created: 10 Apr 2023 9:21:43pm
    Author:  程

  ==============================================================================
*/
#ifndef GrainBuffer_h
#define GrainBuffer_h

#include "JuceHeader.h"

class GrainBuffer {
public:
    
    void setSize(int numSamples) {
        mCircularBuffer.setSize(2, numSamples);
    }
    
    void writeToBuffer(float& inLeft, float& inRight) {
        mCircularBuffer.setSample(0, mWriteHead, inLeft);
        mCircularBuffer.setSample(1, mWriteHead, inRight);
        
        mWriteHead++;
        
        if (mWriteHead >= mCircularBuffer.getNumSamples()) {
            mWriteHead = 0;
        }
    }
    
    float getSample(int inChannel, int inSample) const {
        jassert(juce::isPositiveAndBelow(inSample, mCircularBuffer.getNumSamples()));
        return mCircularBuffer.getSample(inChannel, inSample);
        
    }
    
    int getWriteHead() {
        return mWriteHead;
    }
    
    int getNumSamples() const {
        return mCircularBuffer.getNumSamples();
    }
    
private:
    
    int mWriteHead = 0;
    
    juce::AudioBuffer<float> mCircularBuffer;
    
};

#endif /* GrainBuffer_h */
