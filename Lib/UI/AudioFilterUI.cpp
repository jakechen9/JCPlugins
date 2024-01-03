//
// Created by 程 on 1/1/24.
//

#include "AudioFilterUI.h"

AudioFilterUI::AudioFilterUI(ProcessorInterface *inAudioProcessor) :mFilterProcessorInterface(inAudioProcessor)
{

    auto& tree_state = *mFilterProcessorInterface->getParameterManager()->getValueTree();

    mLPFreq = std::make_unique<SliderContainer>();
    mLPFreq->setParameterToControl(tree_state, PARAM_ID[AppParamID::LPFreq].getParamID());
    addAndMakeVisible(mLPFreq.get());

    mHPFreq = std::make_unique<SliderContainer>();
    mHPFreq->setParameterToControl(tree_state, PARAM_ID[AppParamID::HPFreq].getParamID());
    addAndMakeVisible(mHPFreq.get());
}
AudioFilterUI::~AudioFilterUI() = default;

//void AudioFilterUI::paint(juce::Graphics& g)
//{
////    g.drawImage(mBackGround, 0, 0, 1100, 237,
////                0, 0, mBackGround.getWidth(), mBackGround.getHeight());
//}

void AudioFilterUI::resized()
{
    auto size = 80;
    mHPFreq->setBounds(0, 20, size, size);
    mLPFreq->setBounds(100, 20, size, size);

}