/*
  ==============================================================================

    BottomRow.cpp
    Created: 18 Mar 2023 4:38:17pm
    Author:  程

  ==============================================================================
*/

#include "BottomRow.h"
#include "ParameterManager.h"


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
    
    mDelayWidth = std::make_unique<SliderContainer>();
    mDelayWidth->setParameterToControl(tree_state, ParameterIDStrings[AppParameterID::Width]);
    addAndMakeVisible(mDelayWidth.get());
    
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
//    auto area = getLocalBounds().reduced(5, 0);
//    const int boundHeight = (area.getHeight() - 5) / 4;
    
    mDelayMix->setBounds(61, 94, 70, 70);
    mDelayTime->setBounds(176, 43, 70, 70);
    mDelaySpread->setBounds(176, 151, 70, 70);
    mDelayFeedback->setBounds(301, 43, 70, 70);
    mDelayWidth->setBounds(301, 151, 70, 70);
    mDelayLowpass->setBounds(426, 151, 70, 70);
    mDelayHighpass->setBounds(426, 43, 70, 70);
}
