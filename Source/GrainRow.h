/*
  ==============================================================================

    GrainRow.h
    Created: 3 Apr 2023 9:41:12am
    Author:  程

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "SliderContainer.h"
#include "PluginProcessor.h"


class GrainRow : public juce::Component
{
public:
    GrainRow(Week6AssignmentAudioProcessor&);
    ~GrainRow() override;
    
    void paint(juce::Graphics& g) override;
    void resized() override;
    
private:
//    juce::Label mGrainTitle;
    std::unique_ptr<SliderContainer> mGrainMix;
    std::unique_ptr<SliderContainer> mGrainSize;
    
    
    Week6AssignmentAudioProcessor& audioProcessor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GrainRow)
};
