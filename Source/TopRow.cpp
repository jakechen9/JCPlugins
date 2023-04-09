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
    mFilterMix = std::make_unique<SliderContainer>();
    mFilterMix->setParameterToControl(tree_state, ParameterIDStrings[AppParameterID::FilterMix]);
    addAndMakeVisible(mFilterMix.get());
    
    mLow= std::make_unique<SliderContainer>();
    mLow->setParameterToControl(tree_state, ParameterIDStrings[AppParameterID::Low]);
    addAndMakeVisible(mLow.get());
    
    mHigh = std::make_unique<SliderContainer>();
    mHigh->setParameterToControl(tree_state, ParameterIDStrings[AppParameterID::High]);
    addAndMakeVisible(mHigh.get());
    

}

TopRow::~TopRow() = default;

void TopRow::paint(juce::Graphics& g)
{
    g.setColour(juce::Colour(62, 72, 73));
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 0.f);
}

void TopRow::resized()
{
    mFilterMix->setBounds(176, 55, 70, 70);
    mLow -> setBounds(301, 55, 70, 70);
    mHigh -> setBounds(426, 55, 70, 70);
}
