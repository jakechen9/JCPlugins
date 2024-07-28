//
// Created by 程 on 1/1/24.
//

#ifndef JCPLUGINS_AUDIOFILTERUI_H
#define JCPLUGINS_AUDIOFILTERUI_H
#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "SliderContainer.h"
#include "interfaceDefine.h"

class AudioFilterUI : public juce::Component
{
public:

    explicit AudioFilterUI(ProcessorInterface* inAudioProcessor);
    ~AudioFilterUI() override;

    //    void paint(juce::Graphics& g) override;
    void resized() override;

private:

    std::unique_ptr<SliderContainer> mLPFreq;
    std::unique_ptr<SliderContainer> mHPFreq;
    ProcessorInterface* mFilterProcessorInterface;
    juce::Image mBackGround;
    juce::Label mFilterLabel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioFilterUI)
};

#endif //JCPLUGINS_AUDIOFILTERUI_H
