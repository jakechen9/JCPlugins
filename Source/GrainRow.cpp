/*
  ==============================================================================

    GrainRow.cpp
    Created: 3 Apr 2023 9:41:12am
    Author:  程

  ==============================================================================
*/

#include "GrainRow.h"
#include "ParameterManager.h"

GrainRow::GrainRow(Week6AssignmentAudioProcessor& inAudioProcessor) :
audioProcessor(inAudioProcessor){
    auto& tree_state = audioProcessor.getParameterManager()->getTreeState();
    mGrainMix = std::make_unique<SliderContainer>();
    mGrainMix->setParameterToControl(tree_state, ParameterIDStrings[AppParameterID::GrainMix]);
    addAndMakeVisible(mGrainMix.get());


    mGrainSize = std::make_unique<SliderContainer>();
    mGrainSize->setParameterToControl(tree_state, ParameterIDStrings[AppParameterID::GrainSize]);
    addAndMakeVisible(mGrainSize.get());
}

GrainRow::~GrainRow() = default;

void GrainRow::paint(juce::Graphics& g)
{
    g.setColour(juce::Colour(62, 72, 73));
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 0.f);
}

void GrainRow::resized()
{
//    auto area = getLocalBounds().reduced(5, 0);
//    const int boundHeight = (area.getHeight() - 5) / 4;
    
    mGrainMix->setBounds(61, 94, 70, 70);
    mGrainSize->setBounds(176, 43, 70, 70);
}
