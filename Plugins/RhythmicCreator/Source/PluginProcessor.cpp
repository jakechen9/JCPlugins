/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"

#include <memory>
#include "PluginEditor.h"

//==============================================================================
RhythmicCreatorAudioProcessor::RhythmicCreatorAudioProcessor()
{
    mFilterParameterManager = std::make_unique<ParameterManager>(this);
}

RhythmicCreatorAudioProcessor::~RhythmicCreatorAudioProcessor()
= default;


// Audio

void RhythmicCreatorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mAudioFilterL.initialize(static_cast<float>(sampleRate), samplesPerBlock);
    mAudioFilterR.initialize(static_cast<float>(sampleRate), samplesPerBlock);
}

void RhythmicCreatorAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    (void) midiMessages;
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    float input_gain = 0;
    input_gain += buffer.getMagnitude(0, 0, buffer.getNumSamples());
    input_gain += buffer.getMagnitude(1, 0, buffer.getNumSamples());
    input_gain /= 2;
    mInputGain = input_gain;

    mAudioFilterL.setParameters(mFilterParameterManager->getCurrentParameterValue(LPFreq),
                                mFilterParameterManager->getCurrentParameterValue(HPFreq));
    mAudioFilterR.setParameters(mFilterParameterManager->getCurrentParameterValue(LPFreq),
                                mFilterParameterManager->getCurrentParameterValue(HPFreq));

    mAudioFilterL.processBlock(buffer.getWritePointer(0),
                         buffer.getNumSamples());
    mAudioFilterR.processBlock(buffer.getWritePointer(1),
                         buffer.getNumSamples());

    float output_gain = 0;
    output_gain += buffer.getMagnitude(0, 0, buffer.getNumSamples());
    output_gain += buffer.getMagnitude(1, 0, buffer.getNumSamples());
    output_gain /= 2;
    mOutputGain = output_gain;
}


ParameterManager* RhythmicCreatorAudioProcessor::getParameterManager()
{
    return mFilterParameterManager.get();
}

juce::AudioProcessor* RhythmicCreatorAudioProcessor::getAudioProcessor()
{
    return this;
}

// STATE
//==============================================================================
void RhythmicCreatorAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = mFilterParameterManager->getValueTree()->copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}


void RhythmicCreatorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary (data, sizeInBytes));
    mFilterParameterManager->getValueTree()->replaceState(juce::ValueTree::fromXml(*xmlState));
}

//==============================================================================
juce::AudioProcessorEditor* RhythmicCreatorAudioProcessor::createEditor()
{
    return new RhythmicCreatorAudioProcessorEditor (*this);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new RhythmicCreatorAudioProcessor();
}
