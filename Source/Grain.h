/*
  ==============================================================================

    Grain.h
    Created: 4 Apr 2023 2:39:32pm
    Author:  程

  ==============================================================================
*/

#ifndef Grain_h
#define Grain_h

#include "JuceHeader.h"
#include "AudioHelpers.h"

class Grain {
public:
    
    void setSize(int inGrainSize) {
        mGrainSize = inGrainSize;
    }
    
    void reset() {
        mGrainCounter = 0;
    }
    
    float getNextWindowSample() {
        mGrainCounter++;
        
        auto val = 0.5 * (1 - std::cos(6.283185307179586 * (float)mGrainCounter / (((float)mGrainSize)-1.f)));
        
        return val;
    }
    
    bool isActive() {
        if (mGrainCounter < mGrainSize) {
            return true;
        } else {
            return false;
        }
    }
    
private:
    
    // size in sample
    int mGrainSize  = 0;
    
    // position in sample
    int mGrainCounter = 0;
};

#endif
