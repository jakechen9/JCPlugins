/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "BottomRow.h"
#include "MiddleRow.h"
#include "MyLookAndFeel.h"
#include "PluginProcessor.h"
#include "SliderContainer.h"
#include "TopRow.h"
#include <JuceHeader.h>

//==============================================================================
/**
*/
class JCAudioProcessorEditor : public juce::AudioProcessorEditor,
                               public juce::DragAndDropContainer,
                               public juce::ComponentDragger,
                               public juce::ComponentBoundsConstrainer
{
public:

    explicit JCAudioProcessorEditor(JCAudioProcessor&);
    ~JCAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

private:

    std::unique_ptr<BottomRow> mBottomRow;
    std::unique_ptr<TopRow> mTopRow;
    std::unique_ptr<MiddleRow> mMiddleRow;
    std::unique_ptr<MyLookAndFeel> mLookAndFeel;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JCAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(JCAudioProcessorEditor)
};
