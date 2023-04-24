/*
  ==============================================================================

    BottomRow.cpp
    Created: 18 Mar 2023 4:38:17pm
    Author:  程

  ==============================================================================
*/

#include "BottomRow.h"


BottomRow::BottomRow(Week6AssignmentAudioProcessor& inAudioProcessor) :
audioProcessor(inAudioProcessor){
    auto& tree_state = audioProcessor.getParameterManager()->getTreeState();
    
    mDelayMix = std::make_unique<SliderContainer>();
    mDelayMix->setParameterToControl(tree_state, ParameterIDStrings[AppParameterID::Mix]);
    addAndMakeVisible(mDelayMix.get());
    
    
    mDelayTime = std::make_unique<SliderContainer>();
    mDelayTime->setParameterToControl(tree_state, ParameterIDStrings[AppParameterID::Time]);
    addAndMakeVisible(mDelayTime.get());
    
    mDelaySpread = std::make_unique<SliderContainer>();
    mDelaySpread->setParameterToControl(tree_state, ParameterIDStrings[AppParameterID::Spread]);
    addAndMakeVisible(mDelaySpread.get());
    
    mDelayFeedback = std::make_unique<SliderContainer>();
    mDelayFeedback->setParameterToControl(tree_state, ParameterIDStrings[AppParameterID::Feedback]);
    addAndMakeVisible(mDelayFeedback.get());
    
    mGrainPitch = std::make_unique<SliderContainer>();
    mGrainPitch->setParameterToControl(tree_state, ParameterIDStrings[AppParameterID::GrainPitch]);
    addAndMakeVisible(mGrainPitch.get());
    
    mDelayLowpass = std::make_unique<SliderContainer>();
    mDelayLowpass->setParameterToControl(tree_state, ParameterIDStrings[AppParameterID::Lowpass]);
    addAndMakeVisible(mDelayLowpass.get());
    
    mDelayHighpass = std::make_unique<SliderContainer>();
    mDelayHighpass->setParameterToControl(tree_state, ParameterIDStrings[AppParameterID::Highpass]);
    addAndMakeVisible(mDelayHighpass.get());
    
}

BottomRow::~BottomRow() = default;

void BottomRow::paint(juce::Graphics& g)
{
    g.setColour(juce::Colour(62, 72, 73));
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 0.f);
}

void BottomRow::resized()
{
    float size = 90;

    mDelayMix->setBounds(61*2, 84, size, size);
    mDelayTime->setBounds(176*2, 30, size, size);
    mDelaySpread->setBounds(176*2, 141, size, size);
    mDelayFeedback->setBounds(301*2, 30, size, size);
    mGrainPitch->setBounds(301*2, 141, size, size);
    mDelayLowpass->setBounds(426*2, 141, size, size);
    mDelayHighpass->setBounds(426*2, 30, size, size);
}
