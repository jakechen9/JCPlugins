/*
  ==============================================================================

    MiddleRow.h
    Created: 18 Mar 2023 4:38:06pm
    Author:  程

  ==============================================================================
*/
#pragma once
#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "DraggableButton.h"
#include "SliderContainer.h"
#include "interfaceDefine.h"


class MiddleRow : public juce::Component,
                  public juce::ComponentBoundsConstrainer,
                  public juce::Timer
{
public:
    explicit MiddleRow(ProcessorInterface* inAudioProcessor);
    ~MiddleRow() override;
    
    void paint(juce::Graphics& g) override;
    void resized() override;
    void sanatizePoints();
    void updateBounds();
    void timerCallback() override;
    
private:
    DraggableButton mDraggableAttackButton, mDraggableDecayButton, mDraggableSustainButton, mDraggableReleaseButton;
//    juce::Colour getColour();
    std::unique_ptr<SliderContainer> mAttack;
    ProcessorInterface* mProcessorInterface;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MiddleRow)
};
