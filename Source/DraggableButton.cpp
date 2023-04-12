/*
  ==============================================================================

    DraggableButton.cpp
    Created: 8 Apr 2023 9:21:19pm
    Author:  程

  ==============================================================================
*/

#include "JuceHeader.h"
#include "DraggableButton.h"

DraggableButton::DraggableButton()
{
}

DraggableButton::~DraggableButton()
{
}

void DraggableButton::paint (juce::Graphics& g)
{
    g.setColour (getColour().darker().darker());
    g.fillEllipse (0, 0, getWidth(), getHeight());

    g.setColour (getColour());
    g.fillEllipse (getWidth() / 5.0f, getHeight() / 5.0f, getWidth() / 5.0f * 3, getHeight() / 5.0f * 3);
}

void DraggableButton::resized()
{
}

void DraggableButton::mouseEnter (const juce::MouseEvent& e)
{
    isEntered = true;
}

void DraggableButton::mouseExit (const juce::MouseEvent& e)
{
    isEntered = false;
}

juce::Colour DraggableButton::getColour()
{
    if (mState && isEntered)
        return juce::Colours::hotpink.brighter();
    else if (mState && ! isEntered)
        return juce::Colours::hotpink;

    return juce::Colours::dimgrey;
}

void DraggableButton::setState (const bool state)
{
    mState = state;
}
