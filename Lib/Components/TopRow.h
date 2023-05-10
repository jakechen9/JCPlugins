/*
  ==============================================================================

    TopRow.h
    Created: 18 Mar 2023 4:37:55pm
    Author:  程

  ==============================================================================
*/
#pragma once

#include "JuceHeader.h"
#include "SliderContainer.h"
#include "PluginProcessor.h"
#include "interfaceDefine.h"

class TopRow : public juce::Component
{
public:
    TopRow(ProcessorInterface* inAudioProcessor);
    ~TopRow() override;
    
    void paint(juce::Graphics& g) override;
    void resized() override;
    
private:
    std::unique_ptr<SliderContainer> mAttack;
    std::unique_ptr<SliderContainer> mDecay;
    std::unique_ptr<SliderContainer> mSustain;
    std::unique_ptr<SliderContainer> mRelease;
    std::unique_ptr<SliderContainer> mRate;
    juce::Image mBackGround;
    ProcessorInterface* mProcessorInterface;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TopRow)
};
