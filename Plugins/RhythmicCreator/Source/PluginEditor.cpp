/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
RhythmicCreatorAudioProcessorEditor::RhythmicCreatorAudioProcessorEditor (RhythmicCreatorAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    mLookAndFeel = std::make_unique<MyLookAndFeel>();
    
    setSize (1100, 720);
}

RhythmicCreatorAudioProcessorEditor::~RhythmicCreatorAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void RhythmicCreatorAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void RhythmicCreatorAudioProcessorEditor::resized()
{

}



