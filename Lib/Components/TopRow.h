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

class TopRow : public juce::Component
{
public:
    TopRow(Week6AssignmentAudioProcessor&);
    ~TopRow() override;
    
    void paint(juce::Graphics& g) override;
    void resized() override;
    
private:
    std::unique_ptr<SliderContainer> mAttack;
    std::unique_ptr<SliderContainer> mDecay;
    std::unique_ptr<SliderContainer> mSustain;
    std::unique_ptr<SliderContainer> mRelease;
    
    Week6AssignmentAudioProcessor& audioProcessor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TopRow)
};
