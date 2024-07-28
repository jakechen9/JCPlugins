/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"
#include "PluginProcessor.h"

//==============================================================================
RhythmicCreatorAudioProcessorEditor::RhythmicCreatorAudioProcessorEditor(RhythmicCreatorAudioProcessor& p)
: AudioProcessorEditor(&p),
  audioProcessor(p)
{
    mLookAndFeel = std::make_unique<MyLookAndFeel>();
    setLookAndFeel(mLookAndFeel.get());

    mAudioFilterUI = std::make_unique<AudioFilterUI>(&audioProcessor);
    addAndMakeVisible(mAudioFilterUI.get());

    setSize(1100, 360);
}

RhythmicCreatorAudioProcessorEditor::~RhythmicCreatorAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void RhythmicCreatorAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void RhythmicCreatorAudioProcessorEditor::resized()
{
    mAudioFilterUI->setBounds(0, 0, 1100, 360);
}
