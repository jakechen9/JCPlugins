/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JCAudioProcessor::JCAudioProcessor()
{
    mParameterManager = std::make_unique<ParameterManager>(this);
}

JCAudioProcessor::~JCAudioProcessor() = default;

// Audio

void JCAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    mDelayL.initialize(static_cast<float>(sampleRate), samplesPerBlock);
    mDelayR.initialize(static_cast<float>(sampleRate), samplesPerBlock);
}

void JCAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    (void)midiMessages;
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    float input_gain = 0;
    input_gain += buffer.getMagnitude(0, 0, buffer.getNumSamples());
    input_gain += buffer.getMagnitude(1, 0, buffer.getNumSamples());
    input_gain /= 2;
    mInputGain = input_gain;

    juce::AudioPlayHead::CurrentPositionInfo mTempoInfo;
    getPlayHead()->getCurrentPosition(mTempoInfo);
    auto bpm = juce::jmax(static_cast<float>(mTempoInfo.bpm), 1.f);

    auto noteLength = getTimeDivisonSamples(
        static_cast<int>(mParameterManager->getCurrentParameterValue(Rate)), static_cast<float>(getSampleRate()), bpm);
    auto time_div = TIMEDIV(static_cast<int>(mParameterManager->getCurrentParameterValue(Rate)), bpm);

    // Set Delay Parameter to control
    mDelayL.setParameters(mParameterManager->getCurrentParameterValue(Time),
                          mParameterManager->getCurrentParameterValue(Feedback),
                          mParameterManager->getCurrentParameterValue(Mix),
                          mParameterManager->getCurrentParameterValue(Lowpass),
                          mParameterManager->getCurrentParameterValue(Highpass),
                          mParameterManager->getCurrentParameterValue(GrainPitch),
                          mParameterManager->getCurrentParameterValue(Attack) * time_div,
                          mParameterManager->getCurrentParameterValue(Decay) * time_div,
                          mParameterManager->getCurrentParameterValue(Sustain) * time_div,
                          mParameterManager->getCurrentParameterValue(Release) * time_div,
                          noteLength);

    mDelayR.setParameters(mParameterManager->getCurrentParameterValue(Time),
                          mParameterManager->getCurrentParameterValue(Feedback),
                          mParameterManager->getCurrentParameterValue(Mix),
                          mParameterManager->getCurrentParameterValue(Lowpass),
                          mParameterManager->getCurrentParameterValue(Highpass),
                          mParameterManager->getCurrentParameterValue(GrainPitch),
                          mParameterManager->getCurrentParameterValue(Attack) * time_div,
                          mParameterManager->getCurrentParameterValue(Decay) * time_div,
                          mParameterManager->getCurrentParameterValue(Sustain) * time_div,
                          mParameterManager->getCurrentParameterValue(Release) * time_div,
                          noteLength);

    mDelayL.processBlock(buffer.getWritePointer(0), buffer.getNumSamples());
    mDelayR.processBlock(buffer.getWritePointer(1), buffer.getNumSamples());

    WidthEffect::processBlock(buffer.getWritePointer(0),
                              buffer.getWritePointer(1),
                              mParameterManager->getCurrentParameterValue(Width),
                              buffer.getNumSamples());

    float output_gain = 0;
    output_gain += buffer.getMagnitude(0, 0, buffer.getNumSamples());
    output_gain += buffer.getMagnitude(1, 0, buffer.getNumSamples());
    output_gain /= 2;
    mOutputGain = output_gain;

    // clear buffer when playback stops to avoid super long tails
    if (!mTempoInfo.isPlaying)
        buffer.clear();
}

ParameterManager* JCAudioProcessor::getParameterManager()
{
    return mParameterManager.get();
}

juce::AudioProcessor* JCAudioProcessor::getAudioProcessor()
{
    return this;
}

// STATE
//==============================================================================
void JCAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = mParameterManager->getValueTree()->copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void JCAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    mParameterManager->getValueTree()->replaceState(juce::ValueTree::fromXml(*xmlState));
}

//==============================================================================
juce::AudioProcessorEditor* JCAudioProcessor::createEditor()
{
    return new JCAudioProcessorEditor(*this);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JCAudioProcessor();
}
