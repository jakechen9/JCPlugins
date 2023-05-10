//
// Created by 程 on 5/5/23.
//

#include "ParameterUtil.h"

using namespace ParameterUtil;

void ParameterUtil::createFrequencyParameter(ParameterUtil::Parameters& inParameters,
                                                juce::ParameterID inID,
                                                juce::String inName,
                                                float inMinimum,
                                                float inMaximum,
                                                float inDefaultValue)
{
    auto range = createNormalisableRange<float>(inMinimum, inMaximum, 500.f);
    addParameter<juce::AudioParameterFloat>(inParameters, inID, inName, range,
                                            inDefaultValue, juce::String(),
                                            juce::AudioProcessorParameter::genericParameter,
                                            frequencyToString, nullptr);
}

void ParameterUtil::createPercentageParameter(ParameterUtil::Parameters& inParameters,
                                              juce::ParameterID inID,
                                              juce::String inName,
                                              float inDefaultValue)
{
    auto range = createNormalisableRange<float>(0.f, 1.f, .5f);
    addParameter<juce::AudioParameterFloat>(inParameters, inID, inName, range,
                                            inDefaultValue, juce::String(),
                                            juce::AudioProcessorParameter::genericParameter,
                                            percentageToString, nullptr);
}

void ParameterUtil::createFloatParameter(ParameterUtil::Parameters& inParameters, juce::ParameterID inID, juce::String inName, float inMinimum, float inMaximum, float inDefaultValue, float inCenter)
{
    auto range = createNormalisableRange(inMinimum, inMaximum, inCenter);
    addParameter<juce::AudioParameterFloat>(inParameters, inID, inName, range,
                                            inDefaultValue, juce::String(),
                                            juce::AudioProcessorParameter::genericParameter,
                                            floatToString, nullptr);
}

void ParameterUtil::createTimeDivParameter(ParameterUtil::Parameters& inParameters, juce::ParameterID inID, juce::String inName, float inMinimum, float inMaximum, float inDefaultValue)
{
    int minimum = int(inMinimum);
    int maximum = int(inMaximum);
    int defaultValue = int(inDefaultValue);
    addParameter<juce::AudioParameterInt>(inParameters, inID, inName, minimum, maximum, defaultValue, juce::String(), timedivToString, nullptr);
}

void ParameterUtil::createTimeParameter(ParameterUtil::Parameters& inParameters,
                                        juce::ParameterID inID,
                                        juce::String inName,
                                        float inMinimum,
                                        float inMaximum,
                                        float inDefaultValue)
{
    auto range = createNormalisableRange<float>(inMinimum, inMaximum, .5f);
    addParameter<juce::AudioParameterFloat>(inParameters, inID, inName, range,
                                            inDefaultValue, juce::String(),
                                            juce::AudioProcessorParameter::genericParameter,
                                            timeToString, nullptr);
}