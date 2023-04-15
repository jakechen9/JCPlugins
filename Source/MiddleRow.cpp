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
    g.setColour (juce::Colours::hotpink.withBrightness (0.8f));
    g.setColour (juce::Colours::indianred);
    
    g.setColour(juce::Colour(205, 212, 212));
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 0.f);
    
    mResponseCurve.clear();
    juce::Point<float> startPoint(static_cast<float> (mDraggableAttackButton.getX()), static_cast<float> (mDraggableAttackButton.getY()));
    juce::Point<float> endPoint(static_cast<float> (mDraggableDelayButton.getX()), static_cast<float> (mDraggableDelayButton.getY()));
    mResponseCurve.startNewSubPath(startPoint);
    mResponseCurve.lineTo(endPoint);
    g.strokePath (mResponseCurve, juce::PathStrokeType (5.0f));
//    mResponseCurve.closeSubPath();
}

void MiddleRow::resized()
{
    
    
    float size = getWidth() / 1000.0f * 20;
    mDraggableAttackButton.setBounds(0, 301, size, size);
    mDraggableDelayButton.setBounds(208, 0, size, size);
    mDraggableSustainButton.setBounds(522, 84, size, size);
    mDraggableReleaseButton.setBounds(818, 301, size, size);
}

void MiddleRow::timerCallback()
{
    repaint();
}


