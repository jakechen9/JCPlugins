/*
  ==============================================================================

    ParameterDefines.h
    Created: 9 Mar 2023 6:50:54pm
    Author:  程

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "ParameterUtil.h"

enum AppParamID{
//  Delay Section
    Mix = 0,
    Time,
    Feedback,
    Width,
    Lowpass,
    Highpass,
    
//  Grain Section
    GrainPitch,
    
//  ADSR MOD Section
    Attack,
    Decay,
    Sustain,
    Release,

//  ADSR Rate
    Rate,
    TotalNumberParameters
};

static const juce::Array<juce::ParameterID> PARAM_ID {
//  Delay Section
    juce::ParameterID("Mix",1),
    juce::ParameterID("Time", 1),
    juce::ParameterID("Feedback", 1),
    juce::ParameterID("Width",1),
    juce::ParameterID("Lowpass",1),
    juce::ParameterID("Highpass",1),
    
//  Grain Section
    juce::ParameterID("GrainPitch",1),
    
//  ADSR MOD Section
    juce::ParameterID("Attack",1),
    juce::ParameterID("Decay",1),
    juce::ParameterID("Sustain",1),
    juce::ParameterID("Release",1),

//  ADSR Rate
    juce::ParameterID("Rate",1)
};

static const juce::Array<ParameterUtil::PARAMETER_TYPE> PARAM_TYPE{
//  Delay Section
    ParameterUtil::PercentP,
    ParameterUtil::FloatP,
    ParameterUtil::PercentP,
    ParameterUtil::PercentP,
    ParameterUtil::FreqP,
    ParameterUtil::FreqP,

//  GrainSection
    ParameterUtil::FloatP,

//  ADSR MOD Section
    ParameterUtil::FloatP,
    ParameterUtil::FloatP,
    ParameterUtil::FloatP,
    ParameterUtil::FloatP,

//  ADSR Rate
    ParameterUtil::TimeDivP

};



static const juce::Array<float> ParameterMinimum {
//  Delay Section
    0.f,
    .1f,
    0.f,
    0.f,
    20.f,
    20.f,
    
//  Grain Section
    .3f,
    
//  ADSR MOD Section
    0.f,
    0.f,
    0.f,
    0.f,

//  Rate Minimum
    8.f
};

static const juce::Array<float> ParameterMaximum {
//  Delay Section
    1.f,
    1.f,
    .95f,
    1.f,
    22000.f,
    22000.f,
    
//  Grain Section
    6.f,
    
//  ADSR MOD Section
    1.f,
    1.f,
    1.f,
    1.f,

//  Rate Maximum
    21.f
};

static const juce::Array<float> ParameterDefault {
//  Delay Section
    .5f,
    .5f,
    .5f,
    .5f,
    22000.f,
    20.f,

//  Grain Section
    1.f,
    
//  ADSR MOD Section
    .2f,
    .3f,
    .5f,
    .2f,

//  Rate Default
    12.f
};

static const juce::Array<float> ParameterCenter {
    //  Delay Section
    .5f,
    .5f,
    .5f,
    .5f,
    500.f,
    500.f,

    //  Grain Section
    .5f,

    //  ADSR MOD Section
    .5f,
    .5f,
    .5f,
    .5f,

    //  Rate Default
    18.f
};

