//
// Created by 程 on 5/5/23.
//

#pragma once
#include "JuceHeader.h"

enum TimeDiv {

    OneHundredTwentyEighthNote = 0,
    SixtyFourthNoteTriplet,
    OneHundredTwentyEighthNoteDotted,

    SixtyFourthNote,
    ThirtySecondNoteTriplet,
    SixtyFourthNoteDotted,

    ThirtySecondNote,
    SixteenthNoteTriplet,

    // Minimum
    ThirtySecondNoteDotted,

    SixteenthNote,
    EighthNoteTriplet,
    SixteenthNoteDotted,

    EighthNote,
    QuarterNoteTriplet,
    EighthNoteDotted,

    QuarterNote,
    HalfNoteTriplet,
    QuarterNoteDotted,

    HalfNote,
    OneBarTriplet,
    HalfNoteDotted,
//  Maximum
    OneBar,
    OneBarDotted,
    TwoBar,
    ThreeBar,
    FourBar,
    SixBar,
    EightBar,
    TwelveBar,
    SixteenBar,
    ThirtyTwoBar,
};

static const juce::StringArray TIME_DIVISION_STRINGS {
    "1/128",
    "1/64T",
    "1/128D",

    "1/64",
    "1/32T",
    "1/64D",

    "1/32",
    "1/16T",
    "1/32D",

    "1/16",
    "1/8T",
    "1/16D",

    "1/8",
    "1/4T",
    "1/8D",

    "1/4",
    "1/2T",
    "1/4D",

    "1/2",
    "1/1T",
    "1/2D",

    "1 Bar",
    "1.5 Bars",
    "2 Bars",
    "3 Bars",
    "4 Bars",
    "6 Bars",
    "8 Bars",
    "12 Bars",
    "16 Bars",
    "32 Bars",
};

inline float getTimeDivisonSamples(int inDiv, float inSampleRate, float inBpm)
{
    float samplesPerBeat = ((60.f / inBpm) * inSampleRate);

    switch (inDiv) {
        case ThirtyTwoBar: return samplesPerBeat * 128;
        case SixteenBar: return samplesPerBeat * 64;
        case TwelveBar: return samplesPerBeat * 48;
        case EightBar: return samplesPerBeat * 32;
        case SixBar: return samplesPerBeat * 24;
        case FourBar: return samplesPerBeat * 16;
        case ThreeBar: return samplesPerBeat * 12;
        case TwoBar: return samplesPerBeat * 8;
        case OneBarDotted: return samplesPerBeat * 6;
        case OneBar: return samplesPerBeat * 4;

        case HalfNoteDotted: return (samplesPerBeat * 2) * 1.5;
        case QuarterNoteDotted: return samplesPerBeat * 1.5;
        case EighthNoteDotted: return (samplesPerBeat / 2.f) * 1.5;
        case SixteenthNoteDotted: return (samplesPerBeat / 4.f) * 1.5;
        case ThirtySecondNoteDotted: return (samplesPerBeat / 8.f) * 1.5;
        case SixtyFourthNoteDotted: return (samplesPerBeat / 16.f) * 1.5;
        case OneHundredTwentyEighthNoteDotted: return (samplesPerBeat / 32.f) * 1.5;

        case HalfNote: return samplesPerBeat * 2;
        case QuarterNote: return samplesPerBeat;
        case EighthNote: return samplesPerBeat / 2.f;
        case SixteenthNote: return samplesPerBeat / 4.f;
        case ThirtySecondNote: return samplesPerBeat / 8.f;
        case SixtyFourthNote: return samplesPerBeat / 16.f;
        case OneHundredTwentyEighthNote: return samplesPerBeat / 32.f;

        case OneBarTriplet:  return (samplesPerBeat * 4) / 1.5;
        case HalfNoteTriplet: return (samplesPerBeat * 2) / 1.5;
        case QuarterNoteTriplet: return (samplesPerBeat) / 1.5;
        case EighthNoteTriplet: return (samplesPerBeat / 2.f) / 1.5;
        case SixteenthNoteTriplet: return (samplesPerBeat / 4.f) / 1.5;
        case ThirtySecondNoteTriplet: return (samplesPerBeat / 8.f) / 1.5;
        case SixtyFourthNoteTriplet: return (samplesPerBeat / 16.f) / 1.5;

        default: return -1;
    }
};


inline float TIMEDIV(int inDiv, float inBpm)
{
    float secondsPerBeat = (60.f / inBpm);

    switch (inDiv) {
        case ThirtyTwoBar: return secondsPerBeat * 128;
        case SixteenBar: return secondsPerBeat * 64;
        case TwelveBar: return secondsPerBeat * 48;
        case EightBar: return secondsPerBeat * 32;
        case SixBar: return secondsPerBeat * 24;
        case FourBar: return secondsPerBeat * 16;
        case ThreeBar: return secondsPerBeat * 12;
        case TwoBar: return secondsPerBeat * 8;
        case OneBarDotted: return secondsPerBeat * 6;
        case OneBar: return secondsPerBeat * 4;

        case HalfNoteDotted: return (secondsPerBeat * 2) * 1.5;
        case QuarterNoteDotted: return secondsPerBeat * 1.5;
        case EighthNoteDotted: return (secondsPerBeat / 2.f) * 1.5;
        case SixteenthNoteDotted: return (secondsPerBeat / 4.f) * 1.5;
        case ThirtySecondNoteDotted: return (secondsPerBeat / 8.f) * 1.5;
        case SixtyFourthNoteDotted: return (secondsPerBeat / 16.f) * 1.5;
        case OneHundredTwentyEighthNoteDotted: return (secondsPerBeat / 32.f) * 1.5;

        case HalfNote: return secondsPerBeat * 2;
        case QuarterNote: return secondsPerBeat;
        case EighthNote: return secondsPerBeat / 2.f;
        case SixteenthNote: return secondsPerBeat / 4.f;
        case ThirtySecondNote: return secondsPerBeat / 8.f;
        case SixtyFourthNote: return secondsPerBeat / 16.f;
        case OneHundredTwentyEighthNote: return secondsPerBeat / 32.f;

        case OneBarTriplet:  return (secondsPerBeat * 4) / 1.5;
        case HalfNoteTriplet: return (secondsPerBeat * 2) / 1.5;
        case QuarterNoteTriplet: return (secondsPerBeat) / 1.5;
        case EighthNoteTriplet: return (secondsPerBeat / 2.f) / 1.5;
        case SixteenthNoteTriplet: return (secondsPerBeat / 4.f) / 1.5;
        case ThirtySecondNoteTriplet: return (secondsPerBeat / 8.f) / 1.5;
        case SixtyFourthNoteTriplet: return (secondsPerBeat / 16.f) / 1.5;

        default: return -1;
    }
};