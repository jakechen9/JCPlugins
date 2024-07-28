//
// Created by 程 on 1/3/24.
//

#ifndef JCPLUGINS_PLUGINPROCESSORBASE_H
#define JCPLUGINS_PLUGINPROCESSORBASE_H
#include "JuceHeader.h"

class PluginProcessorBase : public juce::AudioProcessor
{
public:

    PluginProcessorBase();

    ~PluginProcessorBase() override;

    bool hasEditor() const override;
    //==============================================================================
    /* general functions which tell the DAW information about your plugin -- you made need sometimes */
    const juce::String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;
    void releaseResources() override;
#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

private:
};

#endif //JCPLUGINS_PLUGINPROCESSORBASE_H
