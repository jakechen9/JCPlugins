/*
  ==============================================================================

    TopRow.cpp
    Created: 18 Mar 2023 4:37:55pm
    Author:  程

  ==============================================================================
*/

#include "TopRow.h"

TopRow::TopRow(ProcessorInterface* inAudioProcessor) :mProcessorInterface(inAudioProcessor){

    mBackGround = juce::ImageCache::getFromMemory(BinaryData::LFOParamFrame_png, BinaryData::LFOParamFrame_pngSize);

    auto& tree_state = *mProcessorInterface->getParameterManager()->getValueTree();

    
    mAttack = std::make_unique<SliderContainer>();
    mAttack->setParameterToControl(tree_state, PARAM_ID[AppParamID::Attack].getParamID());
    addAndMakeVisible(mAttack.get());
    
    mDecay = std::make_unique<SliderContainer>();
    mDecay->setParameterToControl(tree_state, PARAM_ID[AppParamID::Decay].getParamID());
    addAndMakeVisible(mDecay.get());
    
    mSustain = std::make_unique<SliderContainer>();
    mSustain->setParameterToControl(tree_state, PARAM_ID[AppParamID::Sustain].getParamID());
    addAndMakeVisible(mSustain.get());
    
    mRelease = std::make_unique<SliderContainer>();
    mRelease->setParameterToControl(tree_state, PARAM_ID[AppParamID::Release].getParamID());
    addAndMakeVisible(mRelease.get());

    mRate = std::make_unique<SliderContainer>();
    mRate->setParameterToControl(tree_state, PARAM_ID[AppParamID::Rate].getParamID());
    addAndMakeVisible(mRate.get());
}

TopRow::~TopRow() = default;

void TopRow::paint(juce::Graphics& g)
{
    g.drawImage(mBackGround, 0, 0, 1100, 160, 0, 0, mBackGround.getWidth(), mBackGround.getHeight());
//    g.setColour(juce::Colour(62, 72, 73));
//    g.fillRoundedRectangle(getLocalBounds().toFloat(), 0.f);
}

void TopRow::resized()
{
    auto size = 100;
    auto knob_y = (getLocalBounds().getCentreY()) - size / 2;
    mRate -> setBounds(176, knob_y, size, size);
    mAttack -> setBounds(351, knob_y, size, size);
    mDecay -> setBounds(525, knob_y, size, size);
    mSustain -> setBounds(700, knob_y, size, size);
    mRelease -> setBounds(875, knob_y, size, size);
}
