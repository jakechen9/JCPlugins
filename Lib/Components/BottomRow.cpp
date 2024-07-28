/*
  ==============================================================================

    BottomRow.cpp
    Created: 18 Mar 2023 4:38:17pm
    Author:  程

  ==============================================================================
*/

#include "BottomRow.h"

BottomRow::BottomRow(ProcessorInterface* inAudioProcessor)
: mProcessorInterface(inAudioProcessor)
{

    mBackGround =
        juce::ImageCache::getFromMemory(BinaryData::DelayGrainParamFrame_png, BinaryData::DelayGrainParamFrame_pngSize);

    auto& tree_state = *mProcessorInterface->getParameterManager()->getValueTree();

    mDelayMix = std::make_unique<SliderContainer>();
    mDelayMix->setParameterToControl(tree_state, PARAM_ID[AppParamID::Mix].getParamID());
    addAndMakeVisible(mDelayMix.get());

    mDelayTime = std::make_unique<SliderContainer>();
    mDelayTime->setParameterToControl(tree_state, PARAM_ID[AppParamID::Time].getParamID());
    addAndMakeVisible(mDelayTime.get());

    mDelayWidth = std::make_unique<SliderContainer>();
    mDelayWidth->setParameterToControl(tree_state, PARAM_ID[AppParamID::Width].getParamID());
    addAndMakeVisible(mDelayWidth.get());

    mDelayFeedback = std::make_unique<SliderContainer>();
    mDelayFeedback->setParameterToControl(tree_state, PARAM_ID[AppParamID::Feedback].getParamID());
    addAndMakeVisible(mDelayFeedback.get());

    mGrainPitch = std::make_unique<SliderContainer>();
    mGrainPitch->setParameterToControl(tree_state, PARAM_ID[AppParamID::GrainPitch].getParamID());
    addAndMakeVisible(mGrainPitch.get());

    mDelayLowpass = std::make_unique<SliderContainer>();
    mDelayLowpass->setParameterToControl(tree_state, PARAM_ID[AppParamID::Lowpass].getParamID());
    addAndMakeVisible(mDelayLowpass.get());

    mDelayHighpass = std::make_unique<SliderContainer>();
    mDelayHighpass->setParameterToControl(tree_state, PARAM_ID[AppParamID::Highpass].getParamID());
    addAndMakeVisible(mDelayHighpass.get());
}

BottomRow::~BottomRow() = default;

void BottomRow::paint(juce::Graphics& g)
{
    g.drawImage(mBackGround, 0, 0, 1100, 237, 0, 0, mBackGround.getWidth(), mBackGround.getHeight());
}

void BottomRow::resized()
{
    auto size = 100;
    mDelayMix->setBounds(61 * 2, 80, size, size);
    mDelayTime->setBounds(176 * 2, 28, size, size);
    mDelayWidth->setBounds(176 * 2, 135, size, size);
    mDelayFeedback->setBounds(301 * 2, 28, size, size);
    mGrainPitch->setBounds(301 * 2, 135, size, size);
    mDelayLowpass->setBounds(426 * 2, 135, size, size);
    mDelayHighpass->setBounds(426 * 2, 28, size, size);
}
