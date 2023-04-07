/*
  ==============================================================================

    ParameterDefines.h
    Created: 9 Mar 2023 6:50:54pm
    Author:  程

  ==============================================================================
*/

#pragma once

enum AppParameterID{
    Mix = 0,
    Time,
    Spread,
    Feedback,
    Width,
    Lowpass,
    Highpass,
    GrainSize,
    GrainMix,
    TotalNumberParameters
};

static juce::Array<juce::String> ParameterIDStrings {
    "Mix",
    "Time",
    "Spread",
    "Feedback",
    "Width",
    "Lowpass",
    "Highpass",
    "GrainSize",
    "GrainMix"
};

static juce::Array<float> ParameterMinimum {
    0.f,
    .1f,
    0.f,
    0.f,
    0.f,
    20.f,
    20.f,
    0.f,
    0.f
};

static juce::Array<float> ParameterMaximum {
    1.f,
    1.f,
    500.f,
    .95f,
    100.f,
    22000.f,
    22000.f,
    10.f,
    1.f
};

static juce::Array<float> ParameterDefault {
    .5f,
    .5f,
    0.f,
    .5f,
    50.f,
    22000.f,
    20.f,
    5.f,
    .5f
};

