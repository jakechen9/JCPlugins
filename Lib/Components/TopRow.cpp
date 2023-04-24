/*
  ==============================================================================

    TopRow.cpp
    Created: 18 Mar 2023 4:37:55pm
    Author:  程

  ==============================================================================
*/

#include "TopRow.h"

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
    
    mAttack = std::make_unique<SliderContainer>();
    mAttack->setParameterToControl(tree_state, ParameterIDStrings[AppParameterID::Attack]);
    addAndMakeVisible(mAttack.get());
    
    mDecay = std::make_unique<SliderContainer>();
    mDecay->setParameterToControl(tree_state, ParameterIDStrings[AppParameterID::Decay]);
    addAndMakeVisible(mDecay.get());
    
    mSustain = std::make_unique<SliderContainer>();
    mSustain->setParameterToControl(tree_state, ParameterIDStrings[AppParameterID::Sustain]);
    addAndMakeVisible(mSustain.get());
    
    mRelease = std::make_unique<SliderContainer>();
    mRelease->setParameterToControl(tree_state, ParameterIDStrings[AppParameterID::Release]);
    addAndMakeVisible(mRelease.get());
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
    mAttack -> setBounds(611, 55, 70, 70);
    mDecay -> setBounds(726, 55, 70, 70);
    mSustain -> setBounds(851, 55, 70, 70);
    mRelease -> setBounds(976, 55, 70, 70);
}
