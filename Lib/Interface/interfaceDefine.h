//
// Created by 程 on 5/5/23.
//

#ifndef JCFINALDELAY_INTERFACEDEFINE_H
#define JCFINALDELAY_INTERFACEDEFINE_H

#include "JuceHeader.h"

class ParameterManager;

class ProcessorInterface
{

public:

    virtual ~ProcessorInterface() = default;

    virtual ParameterManager* getParameterManager() = 0;

    virtual juce::AudioProcessor* getAudioProcessor() = 0;
};

#endif //JCFINALDELAY_INTERFACEDEFINE_H
