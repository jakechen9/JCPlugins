/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Week6AssignmentAudioProcessor::Week6AssignmentAudioProcessor()
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
Week6AssignmentAudioProcessor::~Week6AssignmentAudioProcessor()
{
}


// Audio

void Week6AssignmentAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mDelayL.initialize(sampleRate, samplesPerBlock);
    mDelayR.initialize(sampleRate, samplesPerBlock);

    
}

void Week6AssignmentAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
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
//    DBG(bpm);
    // trigger quarter note
//    float samplePerBeats = (60.f/bpm) * getSampleRate();
//    // 1/8 note
//    float eighthNote = samplePerBeats / 2.f;
//    // time division
//    float time_div = (60.f/bpm) / 2.f;

    auto noteLength = getTimeDivisonSamples(mParameterManager->getCurrentParameterValue(Rate), getSampleRate(), bpm);
    auto time_div = TIMEDIV(mParameterManager->getCurrentParameterValue(Rate), bpm);

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

    /* */
//    DBG("mDelay");
//    float Delay_Left = 0.f;

    mDelayL.processBlock(buffer.getWritePointer(0),
                         buffer.getNumSamples());
    mDelayR.processBlock(buffer.getWritePointer(1),
                         buffer.getNumSamples());

    /* */
//    auto* buffer_write_left = buffer.getWritePointer(0);
//    auto* buffer_write_right = buffer.getWritePointer(1);
//
//    for (int i = 0; i < buffer.getNumSamples(); i++)
//    {
//        Delay_Left *= buffer_write_left[i];
//        Delay_Left *= buffer_write_right[i];
//    }
//
//    DBG(Delay_Left);
//
//    Delay_Left = 0;
//
//
//    DBG("Width:");
//    Delay_Left = 0;
    /* */

    mWidth.processBlock(buffer.getWritePointer(0),
                        buffer.getWritePointer(1),
                        mParameterManager->getCurrentParameterValue(Width),
                        buffer.getNumSamples());
    /* */
//    for (int i = 0; i < buffer.getNumSamples(); i++)
//    {
//        Delay_Left *= buffer_write_left[i];
//        Delay_Left *= buffer_write_right[i];
//    }
//
//    DBG(Delay_Left);
    /* */
    float output_gain = 0;
    output_gain += buffer.getMagnitude(0, 0, buffer.getNumSamples());
    output_gain += buffer.getMagnitude(1, 0, buffer.getNumSamples());
    output_gain /= 2;
    mOutputGain = output_gain;
}


ParameterManager* Week6AssignmentAudioProcessor::getParameterManager()
{
    return mParameterManager.get();
}

juce::AudioProcessor* Week6AssignmentAudioProcessor::getAudioProcessor()
{
    return this;
}

// STATE
//==============================================================================
void Week6AssignmentAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = mParameterManager->getValueTree()->copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}


void Week6AssignmentAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary (data, sizeInBytes));
    mParameterManager->getValueTree()->replaceState(juce::ValueTree::fromXml(*xmlState));
}




//==============================================================================
const juce::String Week6AssignmentAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Week6AssignmentAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Week6AssignmentAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Week6AssignmentAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Week6AssignmentAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Week6AssignmentAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Week6AssignmentAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Week6AssignmentAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Week6AssignmentAudioProcessor::getProgramName (int index)
{
    return {};
}

void Week6AssignmentAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================


void Week6AssignmentAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Week6AssignmentAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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
bool Week6AssignmentAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Week6AssignmentAudioProcessor::createEditor()
{
    return new Week6AssignmentAudioProcessorEditor (*this);
}



//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Week6AssignmentAudioProcessor();
}
