/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "AudioFilters.h"
#include "ParameterManager.h"
#include "PluginProcessorBase.h"
#include "interfaceDefine.h"
#include <JuceHeader.h>

//==============================================================================
/**
*/
class RhythmicCreatorAudioProcessor : public PluginProcessorBase,
                                      public ProcessorInterface
{
public:

    //==============================================================================
    RhythmicCreatorAudioProcessor();
    ~RhythmicCreatorAudioProcessor() override;

    //==============================================================================
    /* PRIMARY PROCESSOR RESPONSIBILITIES*/
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    /* PROCESSOR INTERACE OVERRIDES*/
    ParameterManager* getParameterManager() override;
    AudioProcessor* getAudioProcessor() override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;

private:

    std::unique_ptr<ParameterManager> mFilterParameterManager;
    AudioFilter mAudioFilterL;
    AudioFilter mAudioFilterR;
    float mInputGain = 0;
    float mOutputGain = 0;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RhythmicCreatorAudioProcessor)
};
