/*
  ==============================================================================

    ADSR.h
    Created: 16 Apr 2023 3:15:10pm
    Author:  程

  ==============================================================================
*/
#ifndef ADSR_h
#define ADSR_h

#include "JuceHeader.h"
class ADSR : public juce::ADSR
{
public:
    
    /* */
    ADSR();
    
    /* */
    ~ADSR();
    
    void setParameters(float inAttack, float inDecay, float inSustain, float inRelease);
    
private:
    juce::ADSR mADSR;
};
# endif
