/*
  ==============================================================================

    MiddleRow.h
    Created: 18 Mar 2023 4:38:06pm
    Author:  程

  ==============================================================================
*/
#pragma once
#include "JuceHeader.h"
#include "SliderContainer.h"
#include "PluginProcessor.h"
#include "DraggableButton.h"

class MiddleRow : public juce::Component,
                  public juce::ComponentBoundsConstrainer
{
public:
    MiddleRow(Week6AssignmentAudioProcessor&);
    ~MiddleRow() override;
    
    void paint(juce::Graphics& g) override;
    void resized() override;
    
    void sanatizePoints();
    
private:
    DraggableButton mDraggableAttackButton, mDraggableDecayButton, mDraggableSustainButton, mDraggableReleaseButton;
    juce::Colour getColour();
    Week6AssignmentAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MiddleRow)
};
