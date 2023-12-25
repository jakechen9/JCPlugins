/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "MyLookAndFeel.h"

//==============================================================================
/**
*/
class RhythmicCreatorAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    explicit RhythmicCreatorAudioProcessorEditor (RhythmicCreatorAudioProcessor&);
    ~RhythmicCreatorAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    std::unique_ptr<MyLookAndFeel> mLookAndFeel;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    RhythmicCreatorAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RhythmicCreatorAudioProcessorEditor)
};
