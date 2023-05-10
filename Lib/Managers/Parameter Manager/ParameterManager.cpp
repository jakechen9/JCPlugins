/*
  ==============================================================================

    ParameterManager.cpp
    Created: 9 Mar 2023 6:50:10pm
    Author:  程

  ==============================================================================
*/

#include "ParameterManager.h"


ParameterManager::ParameterManager(ProcessorInterface* inAudioProcessor)
:mProcessorInterface(inAudioProcessor)
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;

    for (int i = 0; i < TotalNumberParameters; i++) {
        switch (PARAM_TYPE[i]){
            case ParameterUtil::FreqP:
                ParameterUtil::createFrequencyParameter(parameters, PARAM_ID[i], PARAM_ID[i].getParamID(), ParameterMinimum[i], ParameterMaximum[i], ParameterDefault[i]);
                break;
            case ParameterUtil::TimeDivP:
                ParameterUtil::createTimeDivParameter(parameters, PARAM_ID[i], PARAM_ID[i].getParamID(), ParameterMinimum[i], ParameterMaximum[i], ParameterDefault[i]);
                break;
            case ParameterUtil::FloatP:
                ParameterUtil::createFloatParameter(parameters, PARAM_ID[i], PARAM_ID[i].getParamID(), ParameterMinimum[i], ParameterMaximum[i], ParameterDefault[i], ParameterCenter[i]);
                break;
            case ParameterUtil::PercentP:
                ParameterUtil::createPercentageParameter(parameters, PARAM_ID[i], PARAM_ID[i].getParamID(),  ParameterDefault[i]);
                break;
            case ParameterUtil::TimeP:
                ParameterUtil::createTimeParameter(parameters, PARAM_ID[i], PARAM_ID[i].getParamID(), ParameterMinimum[i], ParameterMaximum[i], ParameterDefault[i]);
                break;
        }
//        mParameterValues.add(mParameterState.getRawParameterValue(ParameterIDStrings[i]));
    }
    mParameterState.reset(new juce::AudioProcessorValueTreeState(*mProcessorInterface ->getAudioProcessor(), nullptr,
                                                                 "PARAMETER_STATE", {parameters.begin(),parameters.end()}));
}


float ParameterManager::getCurrentParameterValue(int inParameterID)
{
    return mParameterState->getRawParameterValue(PARAM_ID[inParameterID].getParamID()) -> load();
}


void ParameterManager:: getParameter(int inParameterID, float inValue)
{
    mParameterState->getParameter(PARAM_ID[inParameterID].getParamID())->setValueNotifyingHost(inValue);
}


juce::AudioProcessorValueTreeState* ParameterManager::getValueTree()
{
    return mParameterState.get();
}