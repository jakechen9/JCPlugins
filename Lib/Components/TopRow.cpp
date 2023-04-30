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
    auto size = 90;
    auto knob_y = (getLocalBounds().getCentreY()) - size / 2;
    mAttack -> setBounds(61*2, knob_y, size, size);
    mDecay -> setBounds(176*2, knob_y, size, size);
    mSustain -> setBounds(301*2, knob_y, size, size);
    mRelease -> setBounds(426*2, knob_y, size, size);
}
