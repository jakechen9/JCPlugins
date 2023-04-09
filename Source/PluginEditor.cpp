/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ParameterDefines.h"

//==============================================================================
Week6AssignmentAudioProcessorEditor::Week6AssignmentAudioProcessorEditor (Week6AssignmentAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    
    setLookAndFeel(&mLookAndFeel);
    
    mTopRow = std::make_unique<TopRow>(audioProcessor);
    addAndMakeVisible(mTopRow.get());
  
    mBottomRow = std::make_unique<BottomRow>(audioProcessor);
    addAndMakeVisible(mBottomRow.get());
    
    mGrainRow = std::make_unique<GrainRow>(audioProcessor);
    addAndMakeVisible(mGrainRow.get());
    
    setSize (1100, 720);
}

Week6AssignmentAudioProcessorEditor::~Week6AssignmentAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void Week6AssignmentAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void Week6AssignmentAudioProcessorEditor::resized()
{
    mBottomRow->setBounds(0, 483, 550, 237);
    mGrainRow -> setBounds(550, 483, 550, 237);
    mTopRow -> setBounds(0, 0, 1100, 160);
}

