/*
  ==============================================================================

    TopRow.cpp
    Created: 18 Mar 2023 4:37:55pm
    Author:  程

  ==============================================================================
*/

#include "TopRow.h"
#include "ParameterManager.h"
/* Set*/

TopRow::TopRow(Week6AssignmentAudioProcessor& inAudioProcessor) :
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
    
}

TopRow::~TopRow() = default;

void TopRow::paint(juce::Graphics& g)
{
    g.setColour(juce::Colour(255, 255, 255));
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 0.f);
}

void TopRow::resized()
{
//    auto width = getWidth()/4;
//    auto area = getLocalBounds().reduced(5, 0);
//    const int boundHeight = (area.getHeight() - 5) / 4;
    
    mDelayMix->setBounds(176, 55, 50, 50);
//    mDelayTime->setBounds(area.removeFromLeft(width));
//    mDelaySpread->setBounds(area.removeFromLeft(width));
//    mDelayFeedback->setBounds(area.removeFromLeft(width));
}
