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
    
    TotalNumberParameters
};

static juce::Array<juce::String> ParameterIDStrings {
//  Delay Section
    "Mix",
    "Time",
    "Feedback",
    "Width",
    "Lowpass",
    "Highpass",
    
//  Grain Section
    "GrainPitch",
    
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
    20.f,
    20.f,
    
//  Grain Section
    .3f,
    
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
    1.f
};

static juce::Array<float> ParameterDefault {
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
    .2f
};

