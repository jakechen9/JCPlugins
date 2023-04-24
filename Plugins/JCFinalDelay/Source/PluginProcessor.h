/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Delay.h"
#include "ParameterManager.h"
#include "Grain.h"
#include "Filter.h"
#include "WidthEffect.h"
//#include "ADSR.h"

//==============================================================================
/**
*/
class Week6AssignmentAudioProcessor  : public juce::AudioProcessor,
                                      public juce::ADSR
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    Week6AssignmentAudioProcessor();
    ~Week6AssignmentAudioProcessor() override;

    //==============================================================================
    juce::AudioProcessorValueTreeState::ParameterLayout getParameterLayout();
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

   

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    ParameterManager* getParameterManager();

private:
    ParameterManager mParameterManager;
    
    float mInputGain = 0;
    float mOutputGain = 0;
    Delay mDelayL;
    Delay mDelayR;
    Filter mFilterL;
    Filter mFilterR;
    WidthEffect mWidth;
    juce::ADSR mADSR;
    bool mADSRStarted = false;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Week6AssignmentAudioProcessor)
};
