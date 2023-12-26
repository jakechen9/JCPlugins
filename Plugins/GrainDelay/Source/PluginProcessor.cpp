/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JCAudioProcessor::JCAudioProcessor()
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
JCAudioProcessor::~JCAudioProcessor()
= default;


// Audio

void JCAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mDelayL.initialize(static_cast<float>(sampleRate), samplesPerBlock);
    mDelayR.initialize(static_cast<float>(sampleRate), samplesPerBlock);

    
}

void JCAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
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

    juce::AudioPlayHead::CurrentPositionInfo mTempoInfo;
    getPlayHead()->getCurrentPosition(mTempoInfo);
    auto bpm = juce::jmax(static_cast<float>(mTempoInfo.bpm), 1.f);

    auto noteLength = getTimeDivisonSamples(static_cast<int>(mParameterManager->getCurrentParameterValue(Rate)),
                                            static_cast<float>(getSampleRate()), bpm);
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
                          noteLength
                          );
    
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
                          noteLength
                          );


    mDelayL.processBlock(buffer.getWritePointer(0),
                         buffer.getNumSamples());
    mDelayR.processBlock(buffer.getWritePointer(1),
                         buffer.getNumSamples());



    WidthEffect::processBlock(buffer.getWritePointer(0),
                        buffer.getWritePointer(1),
                        mParameterManager->getCurrentParameterValue(Width),
                        buffer.getNumSamples());

    float output_gain = 0;
    output_gain += buffer.getMagnitude(0, 0, buffer.getNumSamples());
    output_gain += buffer.getMagnitude(1, 0, buffer.getNumSamples());
    output_gain /= 2;
    mOutputGain = output_gain;
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
void JCAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = mParameterManager->getValueTree()->copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}


void JCAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary (data, sizeInBytes));
    mParameterManager->getValueTree()->replaceState(juce::ValueTree::fromXml(*xmlState));
}




//==============================================================================
const juce::String JCAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool JCAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JCAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JCAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double JCAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JCAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int JCAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JCAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String JCAudioProcessor::getProgramName (int index)
{
    return {};
}

void JCAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================


void JCAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JCAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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
bool JCAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* JCAudioProcessor::createEditor()
{
    return new JCAudioProcessorEditor (*this);
}



//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JCAudioProcessor();
}
