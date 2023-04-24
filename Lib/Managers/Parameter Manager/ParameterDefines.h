/*
  ==============================================================================

    ParameterDefines.h
    Created: 9 Mar 2023 6:50:54pm
    Author:  程

  ==============================================================================
*/

#pragma once

enum AppParameterID{
//  Delay Section
    Mix = 0,
    Time,
    Spread,
    Feedback,
    Width,
    Lowpass,
    Highpass,
    
//  Grain Section
    GrainSize,
    GrainPitch,
    
//  Filter Section
    FilterMix,
    Low,
    High,
    Res,
    
    
//  ADSR MOD Section
    Attack,
    Decay,
    Sustain,
    Release,
    
    TotalNumberParameters
};

static juce::Array<juce::String> ParameterIDStrings {
//  Delay Section
    "Mix",
    "Time",
    "Spread",
    "Feedback",
    "Width",
    "Lowpass",
    "Highpass",
    
//  Grain Section
    "GrainSize",
    "GrainPitch",
    
    
//  Filter Section
    "FilterMix",
    "Low",
    "High",
    "Res",
    
//  ADSR MOD Section
    "Attack",
    "Decay",
    "Sustain",
    "Release"
};

static juce::Array<float> ParameterMinimum {
//  Delay Section
    0.f,
    .1f,
    0.f,
    0.f,
    0.f,
    20.f,
    20.f,
    
//  Grain Section
    .05f,
    .3f,
    
    
//  Filter Section
    0.f,
    20.f,
    20.f,
    0.1f,
    
//  ADSR MOD Section
    0.f,
    0.f,
    0.f,
    0.f
};

static juce::Array<float> ParameterMaximum {
//  Delay Section
    1.f,
    1.f,
    500.f,
    .95f,
    100.f,
    22000.f,
    22000.f,
    
//  Grain Section
    1.f,
    6.f,
    
//  Filter Section
    1.f,
    22000.f,
    22000.f,
    2.f,
    
//  ADSR MOD Section
    1.f,
    1.f,
    1.f,
    1.f
};

static juce::Array<float> ParameterDefault {
//  Delay Section
    .5f,
    .5f,
    0.f,
    .5f,
    50.f,
    22000.f,
    20.f,

//  Grain Section
    .1f,
    1.f,

//  Filter Section
    .5f,
    22000.f,
    20.f,
    .5f,
    
//  ADSR MOD Section
    .2f,
    .3f,
    .5f,
    .2f
};

