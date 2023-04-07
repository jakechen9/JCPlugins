/*
  ==============================================================================

    BottomRow.h
    Created: 18 Mar 2023 4:38:17pm
    Author:  程

  ==============================================================================
*/
#pragma once

#include "JuceHeader.h"
#include "SliderContainer.h"
#include "PluginProcessor.h"

class BottomRow : public juce::Component
{
public:
    BottomRow(Week6AssignmentAudioProcessor&);
    ~BottomRow() override;
    
    void paint(juce::Graphics& g) override;
    void resized() override;
    
private:
    
    std::unique_ptr<SliderContainer> mDelayMix;
    std::unique_ptr<SliderContainer> mDelayTime;
    std::unique_ptr<SliderContainer> mDelaySpread;
    std::unique_ptr<SliderContainer> mDelayFeedback;
    std::unique_ptr<SliderContainer> mDelayWidth;
    std::unique_ptr<SliderContainer> mDelayLowpass;
    std::unique_ptr<SliderContainer> mDelayHighpass;
    
    Week6AssignmentAudioProcessor& audioProcessor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BottomRow)
};

