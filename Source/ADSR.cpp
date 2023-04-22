/*
  ==============================================================================

    ADSR.cpp
    Created: 16 Apr 2023 3:15:10pm
    Author:  程

  ==============================================================================
*/

#include "ADSR.h"
ADSR::ADSR()
{
    
}

ADSR::~ADSR()
{
    
}


void ADSR::setParameters(float inAttack, float inDecay, float inSustain, float inRelease){
    juce::ADSR::Parameters adsr_params;
    adsr_params.attack = inAttack;
    adsr_params.decay = inDecay;
    adsr_params.sustain = inSustain;
    adsr_params.release = inRelease;
    
//    mADSR.setParameters(adsr_params);
}
