/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JCAudioProcessorEditor::JCAudioProcessorEditor (JCAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    mLookAndFeel = std::make_unique<MyLookAndFeel>();
    
    setLookAndFeel(mLookAndFeel.get());
    
    mTopRow = std::make_unique<TopRow>(&audioProcessor);
    addAndMakeVisible(mTopRow.get());
  
    mBottomRow = std::make_unique<BottomRow>(&audioProcessor);
    addAndMakeVisible(mBottomRow.get());
    
    mMiddleRow = std::make_unique<MiddleRow>(&audioProcessor);
    addAndMakeVisible(mMiddleRow.get());
    
    setSize (1100, 720);
}

JCAudioProcessorEditor::~JCAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void JCAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void JCAudioProcessorEditor::resized()
{
    mBottomRow->setBounds(0, 483, 1100, 237);
    mTopRow -> setBounds(0, 0, 1100, 160);
    mMiddleRow -> setBounds(0, 160, 1100, 323);
}



