/*
  ==============================================================================

    MiddleRow.cpp
    Created: 18 Mar 2023 4:38:06pm
    Author:  程

  ==============================================================================
*/

#include "MiddleRow.h"
#include "ParameterManager.h"

MiddleRow::MiddleRow(Week6AssignmentAudioProcessor& inAudioProcessor) :
audioProcessor(inAudioProcessor){
    mDraggableAttackButton.onDrag = [this](){
        sanatizePoints();
    };
    mDraggableDecayButton.onDrag = [this](){
        sanatizePoints();
    };
    mDraggableSustainButton.onDrag = [this](){
        sanatizePoints();
    };
    mDraggableReleaseButton.onDrag = [this](){
        sanatizePoints();
    };
    
    addAndMakeVisible(mDraggableAttackButton);
    addAndMakeVisible(mDraggableDecayButton);
    addAndMakeVisible(mDraggableSustainButton);
    addAndMakeVisible(mDraggableReleaseButton);
}

MiddleRow::~MiddleRow() = default;

void MiddleRow::paint(juce::Graphics& g)
{
    g.setColour (juce::Colours::hotpink.withBrightness (0.8f));
    
    g.setColour(juce::Colour(205, 212, 212));
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 0.f);
    
    float size = getWidth() / 1000.0f * 20;
    
//    juce::ComponentBoundsConstrainer constrainer;
//    constrainer.applyBoundsToComponent(mDraggableAttackButton, mDraggableAttackButton.getBounds().withPosition(0, 301));
//
//    constrainer.applyBoundsToComponent(mDraggableDecayButton, mDraggableDecayButton.getBounds().withY(0));
//
//    constrainer.applyBoundsToComponent(mDraggableReleaseButton, mDraggableReleaseButton.getBounds().withY(301));
    
    juce::Path mResponseCurve;
    juce::Point<float> attackPoint(mDraggableAttackButton.getX() + size / 2.f ,mDraggableAttackButton.getY() + size / 2.f);
    juce::Point<float> decayPoint(mDraggableDecayButton.getX() + size / 2.f,  mDraggableDecayButton.getY() + size / 2.f);
    juce::Point<float> sustainPoint(mDraggableSustainButton.getX() + size / 2.f, mDraggableSustainButton.getY() + size / 2.f);
    juce::Point<float> releasePoint(mDraggableReleaseButton.getX() + size / 2.f, mDraggableReleaseButton.getY() + size / 2.f);
    mResponseCurve.startNewSubPath(attackPoint);
    mResponseCurve.lineTo(decayPoint);
    mResponseCurve.startNewSubPath(decayPoint);
    mResponseCurve.lineTo(sustainPoint);
    mResponseCurve.startNewSubPath(sustainPoint);
    mResponseCurve.lineTo(releasePoint);
    g.setColour (juce::Colours::hotpink.withBrightness (0.8f));
    g.strokePath (mResponseCurve, juce::PathStrokeType (5.0f));
}

void MiddleRow::resized()
{
    float size = getWidth() / 1000.0f * 20;
    mDraggableAttackButton.setBounds(0, 301, size, size);
    mDraggableDecayButton.setBounds(275, 0, size, size);
    mDraggableSustainButton.setBounds(550, 84, size, size);
    mDraggableReleaseButton.setBounds(825, 301, size, size);
}



void MiddleRow::sanatizePoints()
{
    int x  = juce::jlimit(mDraggableAttackButton.getBounds().getX(), mDraggableSustainButton.getBounds().getX(), mDraggableDecayButton.getBounds().getX());
    
    mDraggableDecayButton.setTopLeftPosition(x, 0);
    mDraggableAttackButton.setTopLeftPosition(mDraggableAttackButton.getBounds().getX(), 301);
    
    
    repaint();
}

