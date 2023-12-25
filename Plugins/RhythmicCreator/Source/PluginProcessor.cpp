/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
RhythmicCreatorAudioProcessor::RhythmicCreatorAudioProcessor()
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )


{
    mParameterManager.reset(new ParameterManager(this));
}
RhythmicCreatorAudioProcessor::~RhythmicCreatorAudioProcessor()
{
}


// Audio

void RhythmicCreatorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
}

void RhythmicCreatorAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    

}


ParameterManager* RhythmicCreatorAudioProcessor::getParameterManager()
{
    return mParameterManager.get();
}

juce::AudioProcessor* RhythmicCreatorAudioProcessor::getAudioProcessor()
{
    return this;
}

// STATE
//==============================================================================
void RhythmicCreatorAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = mParameterManager->getValueTree()->copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}


void RhythmicCreatorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary (data, sizeInBytes));
    mParameterManager->getValueTree()->replaceState(juce::ValueTree::fromXml(*xmlState));
}




//==============================================================================
const juce::String RhythmicCreatorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool RhythmicCreatorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool RhythmicCreatorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool RhythmicCreatorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double RhythmicCreatorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int RhythmicCreatorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int RhythmicCreatorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void RhythmicCreatorAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String RhythmicCreatorAudioProcessor::getProgramName (int index)
{
    return {};
}

void RhythmicCreatorAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================


void RhythmicCreatorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool RhythmicCreatorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif



//==============================================================================
bool RhythmicCreatorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

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
