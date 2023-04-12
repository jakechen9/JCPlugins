/*
  ==============================================================================

    MiddleRow.cpp
    Created: 18 Mar 2023 4:38:06pm
    Author:  程

  ==============================================================================
*/

#include "MiddleRow.h"
#include "ParameterManager.h"

MiddleRow::MiddleRow(Week6AssignmentAudioProcessor& inAudioProcessor) :
audioProcessor(inAudioProcessor){
    
    addAndMakeVisible(mDraggableAttackButton);
    addAndMakeVisible(mDraggableDelayButton);
    addAndMakeVisible(mDraggableSustainButton);
    addAndMakeVisible(mDraggableReleaseButton);
}

MiddleRow::~MiddleRow() = default;

void MiddleRow::paint(juce::Graphics& g)
{
//    mDraggableLowButton.setState(true);
    g.setColour (juce::Colours::hotpink.withBrightness (0.8f));
    g.strokePath (mResponseCurve, juce::PathStrokeType (2.0f));
    g.setColour (juce::Colours::hotpink.withBrightness (0.8f).withAlpha (0.2f));
    g.fillPath (mResponseCurve);
    
    g.setColour(juce::Colour(205, 212, 212));
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 0.f);
    
    
    float size = getWidth() / 1000.0f * 20;
    float buttonX = getMouseXYRelative().getX() - size / 2.0f;
    float buttonY = getMouseXYRelative().getY() - size / 2.0f;
    if (buttonX < 0)
        buttonX = 0;
    if (buttonX > getWidth())
        buttonX = getWidth() - size;
    if (buttonY < getHeight() / 48.0f * (24 - 15) - size / 2.0f)
        buttonY = getHeight() / 48.0f * (24 - 15) - size / 2.0f;
    if (buttonY > getHeight() / 48.0f * (24 + 15) - size / 2.0f)
        buttonY = getHeight() / 48.0f * (24 + 15) - size / 2.0f;
    if(mDraggableAttackButton.isMouseButtonDown())
    {
        mDraggableAttackButton.setBounds(getMouseXYRelative().getX() - size / 2.0f, getMouseXYRelative().getY() - size / 2.0f, size, size);
    }
        
}

void MiddleRow::resized()
{
    
    float size = getWidth() / 1000.0f * 20;
//    float buttonX = getMouseXYRelative().getX() - size / 2.0f;
//    float buttonY = getMouseXYRelative().getY() - size / 2.0f;
//    if (buttonX < 0)
//        buttonX = 0;
//    if (buttonX > getWidth())
//        buttonX = getWidth() - size;
//    if (buttonY < getHeight() / 48.0f * (24 - 15) - size / 2.0f)
//        buttonY = getHeight() / 48.0f * (24 - 15) - size / 2.0f;
//    if (buttonY > getHeight() / 48.0f * (24 + 15) - size / 2.0f)
//        buttonY = getHeight() / 48.0f * (24 + 15) - size / 2.0f;
    
    mDraggableAttackButton.setBounds(40, 301, size, size);
    mDraggableDelayButton.setBounds(208, 3, size, size);
    mDraggableSustainButton.setBounds(522, 84, size, size);
    mDraggableReleaseButton.setBounds(818, 301, size, size);

//    mDraggableLowButton.setBounds(40, 301, 20, 20);
}

void MiddleRow::setDraggableButtonBounds()
{
    
    
}


