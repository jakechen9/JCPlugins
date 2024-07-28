/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "Delay.h"
#include "Grain.h"
#include "ParameterManager.h"
#include "PluginProcessorBase.h"
#include "TimeDiv.h"
#include "WidthEffect.h"
#include "interfaceDefine.h"
#include <JuceHeader.h>

//==============================================================================
/**
*/
class JCAudioProcessor : public PluginProcessorBase,
                         public ProcessorInterface
//                                      public juce::ADSR
#if JucePlugin_Enable_ARA
,
                         public juce::AudioProcessorARAExtension
#endif
{
public:

    //==============================================================================
    JCAudioProcessor();
    ~JCAudioProcessor() override;

    //==============================================================================
    /* PRIMARY PROCESSOR RESPONSIBILITIES*/
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    /* PROCESSOR INTERACE OVERRIDES*/
    ParameterManager* getParameterManager() override;
    AudioProcessor* getAudioProcessor() override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;

private:

    std::unique_ptr<ParameterManager> mParameterManager;
    Delay mDelayL;
    Delay mDelayR;
    WidthEffect mWidth;
    float mInputGain = 0;
    float mOutputGain = 0;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(JCAudioProcessor)
};
