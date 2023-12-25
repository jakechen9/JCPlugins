//
// Created by 程 on 5/5/23.
//

#pragma once

#include "JuceHeader.h"
#include "TimeDiv.h"

namespace ParameterUtil
{
using Parameters = std::vector<std::unique_ptr<juce::RangedAudioParameter>>;
using VTSParameter = juce::AudioProcessorValueTreeState::Parameter;

template <typename inParameterType, typename... Args>
    void addParameter(ParameterUtil::Parameters& inParameters, Args&&... args)
    {
        inParameters.push_back(std::make_unique<inParameterType>(std::forward<Args>(args)...));
    }

template <typename inType>
    juce::NormalisableRange<inType> createNormalisableRange(inType start, inType end, inType center)
    {
        auto range = juce::NormalisableRange<inType> { start, end };
        range.setSkewForCentre(center);
        return range;
    }

auto frequencyToString = [](float inFrequency, int) {
    if (inFrequency <= 1000.f) {
        return juce::String(int(inFrequency)) + " Hz";
    } else {
        return juce::String(int(inFrequency / 1000.f)) + " kHz";
    }
};

auto percentageToString = [](float inPercentage, int) {
    juce::String percentage_string = juce::String(int(inPercentage * 100.f));
    return percentage_string + "%";
};

auto timedivToString = [](int inValue, int) { return TIME_DIVISION_STRINGS[inValue]; };

auto floatToString = [](float infloatVal, int)
{
//    juce::String float_String = juce::String(int (infloatVal));
    return juce::String(infloatVal, 2);
};
auto timeToString = [](float inTimeValue, int) {
    if(inTimeValue < 1.f){
        return juce::String(int(inTimeValue * 1000.f)) + " ms";
    } else{
        return juce::String(int(inTimeValue)) + " s";
    }
};

void createFloatParameter(ParameterUtil::Parameters& inParameters,juce::ParameterID inID,
                          juce::String inName,
                          float inMinimum,
                          float inMaximum,
                          float inDefaultValue,
                          float inCenter);
void createPercentageParameter(ParameterUtil::Parameters& inParameters,
                               juce::ParameterID inID,
                               juce::String inName,
                               float inDefaultValue);
void createTimeDivParameter(ParameterUtil::Parameters& inParameters,
                            juce::ParameterID inID,
                            juce::String inName,
                            float inMinimum,
                            float inMaximum,
                            float inDefaultValue);
void createFrequencyParameter(ParameterUtil::Parameters& inParameters,
                              const juce::ParameterID& inID,
                              const juce::String& inName,
                              float inMinimum,
                              float inMaximum,
                              float inDefaultValue);
void createTimeParameter(ParameterUtil::Parameters& inParameters,
                              juce::ParameterID inID,
                              juce::String inName,
                              float inMinimum,
                              float inMaximum,
                              float inDefaultValue);

enum PARAMETER_TYPE{
    FreqP = 0,
    TimeDivP,
    PercentP,
    FloatP,
    TimeP
};
}