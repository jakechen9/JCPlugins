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
#include "interfaceDefine.h"


class ParameterManager{
public:
    
    explicit ParameterManager(ProcessorInterface* inAudioProcessor);
    
    float getCurrentParameterValue(int inParameterID);

    void getParameter(int inParameterID, float inValue);

    juce::AudioProcessorValueTreeState* getValueTree();
    
private:
    std::unique_ptr<juce::AudioProcessorValueTreeState> mParameterState;
    ProcessorInterface* mProcessorInterface;

};
