/*
  ==============================================================================

    ParameterManager.h
    Created: 9 Mar 2023 6:50:10pm
    Author:  程

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "ParameterDefines.h"

class ParameterManager{
public:
    
    ParameterManager(juce::AudioProcessor* inOwnerProcessor);
    
    juce::AudioProcessorValueTreeState::ParameterLayout getParameterLayout();
    
    juce::AudioProcessorValueTreeState& getTreeState();
    
    float getCurrentParameterValue(AppParameterID inParameterID);
    
private:
    juce::Array<std::atomic<float>*> mParameterValues;
    juce::AudioProcessorValueTreeState mParameterState;
};
