/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "AudioFilterUI.h"
#include "MyLookAndFeel.h"
#include "PluginProcessor.h"
#include "SliderContainer.h"
#include <JuceHeader.h>

//==============================================================================
/**
*/
class RhythmicCreatorAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:

    explicit RhythmicCreatorAudioProcessorEditor(RhythmicCreatorAudioProcessor&);
    ~RhythmicCreatorAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

private:

    std::unique_ptr<MyLookAndFeel> mLookAndFeel;
    std::unique_ptr<AudioFilterUI> mAudioFilterUI;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    RhythmicCreatorAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RhythmicCreatorAudioProcessorEditor)
};
