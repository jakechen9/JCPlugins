/*
  ==============================================================================

    SliderContainer.cpp
    Created: 9 Mar 2023 4:26:53pm
    Author:  程

  ==============================================================================
*/

#include "SliderContainer.h"

SliderContainer::SliderContainer()
{
    mSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(mSlider);
    addAndMakeVisible(mLabel);
}

void SliderContainer::setParameterToControl(juce::AudioProcessorValueTreeState& inVTS, const juce::String& inParamID)
{
    mLabel.setText(inParamID, juce::dontSendNotification);
    mAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(inVTS, inParamID, mSlider));
}

void SliderContainer::resized()
{
    auto bounds = getLocalBounds();
    mSlider.setBounds(bounds.removeFromTop(static_cast<int>(getHeight() * .8)));
    mSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, mSlider.getWidth(), static_cast<int>(getHeight() * .2));
    mSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colour(62.f, 72.f, 73.f, 0.f));
    mLabel.setBounds(bounds);
}
