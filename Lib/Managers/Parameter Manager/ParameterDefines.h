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

enum AppParamID {

    //  GrainDelay AppParamID
    //  Delay Section
    Mix = 0,
    Time,
    Feedback,
    Width,
    Lowpass,
    Highpass,
    //  Grain Section
    GrainPitch,
    GrainSize,
    //  ADSR MOD Section
    Attack,
    Decay,
    Sustain,
    Release,
    //  ADSR Rate
    Rate,

    /*
    ==============================================================================
    */

    //  FilterApp Params
    LPFreq,
    HPFreq,

    TotalNumberParameters
};

static const juce::Array<juce::ParameterID> PARAM_ID {

    //  GrainDelay PARAM_ID
    //  Delay Section
    juce::ParameterID("Mix", 1),
    juce::ParameterID("Time", 1),
    juce::ParameterID("Feedback", 1),
    juce::ParameterID("Width", 1),
    juce::ParameterID("Lowpass", 1),
    juce::ParameterID("Highpass", 1),
    //  Grain Section
    juce::ParameterID("GrainPitch", 1),
    juce::ParameterID("GrainSize", 1),
    //  ADSR MOD Section
    juce::ParameterID("Attack", 1),
    juce::ParameterID("Decay", 1),
    juce::ParameterID("Sustain", 1),
    juce::ParameterID("Release", 1),
    //  ADSR Rate
    juce::ParameterID("Rate", 1),

    /*
    ==============================================================================
    */

    //  FilterApp PARAM_ID
    juce::ParameterID("LPFreq", 1),
    juce::ParameterID("HPFreq", 1)
};

static const juce::Array<ParameterUtil::PARAMETER_TYPE> PARAM_TYPE {

    //  GrainDelay PARAM_TYPE
    //  Delay Section
    ParameterUtil::PercentP,
    ParameterUtil::TimeP,
    ParameterUtil::PercentP,
    ParameterUtil::PercentP,
    ParameterUtil::FreqP,
    ParameterUtil::FreqP,
    //  GrainSection
    ParameterUtil::FloatP,
    ParameterUtil::FloatP,
    //  ADSR MOD Section
    ParameterUtil::FloatP,
    ParameterUtil::FloatP,
    ParameterUtil::FloatP,
    ParameterUtil::FloatP,
    //  ADSR Rate
    ParameterUtil::TimeDivP,

    /*
    ==============================================================================
    */

    // FilterApp PARAM_TYPE
    ParameterUtil::FreqP,
    ParameterUtil::FreqP
};

static const juce::Array<float> ParameterMinimum {

    //  GrainDelay ParameterMinimum
    //  Delay Section
    0.f,
    .1f,
    0.f,
    0.f,
    20.f,
    20.f,
    //  Grain Section
    .3f,
    0.005f,
    //  ADSR MOD Section
    0.f,
    0.f,
    0.f,
    0.f,
    //  Rate Minimum
    8.f,

    /*
    ==============================================================================
    */

    // FilterApp ParameterMinimum
    20.f,
    20.f
};

static const juce::Array<float> ParameterMaximum {

    //  GrainDelay ParameterMaximum
    //  Delay Section
    1.f,
    1.f,
    .95f,
    1.f,
    22000.f,
    22000.f,
    //  Grain Section
    6.f,
    1.0f,
    //  ADSR MOD Section
    1.f,
    1.f,
    1.f,
    1.f,
    //  Rate Maximum
    21.f,

    /*
    ==============================================================================
    */

    //  FilterApp ParameterMaximum
    22000.f,
    22000.f
};

static const juce::Array<float> ParameterDefault {

    //  GrainDelay ParameterDefault
    //  Delay Section
    .5f,
    .5f,
    .5f,
    .5f,
    22000.f,
    20.f,
    //  Grain Section
    1.f,
    0.1f,
    //  ADSR MOD Section
    .2f,
    .3f,
    .5f,
    .2f,
    //  Rate Default
    12.f,

    /*
    ==============================================================================
    */

    // FilterApp ParameterDefault
    22000.f,
    20.f
};

static const juce::Array<float> ParameterCenter {

    // GrainDelay ParameterCenter
    //  Delay Section
    .5f,
    .5f,
    .5f,
    .5f,
    500.f,
    500.f,
    //  Grain Section
    3.5f,
    0.1f,
    //  ADSR MOD Section
    .5f,
    .5f,
    .5f,
    .5f,
    //  Rate Default
    18.f,

    /*
    ==============================================================================
    */

    // FilterApp ParameterCenter
    500.f,
    500.f
};
