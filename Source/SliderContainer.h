/*
  ==============================================================================

    SliderContainer.h
    Created: 9 Mar 2023 4:26:53pm
    Author:  程

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class SliderContainer: public juce::Component {
public:
    SliderContainer();
    
    void setParameterToControl(juce::AudioProcessorValueTreeState& inVTS, const juce::String& inParamID);
    
    void resized() override;
    
private:
    juce::Slider mSlider;
    juce::Label mLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mAttachment;
};
