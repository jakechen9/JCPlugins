/*
  ==============================================================================

    MiddleRow.cpp
    Created: 18 Mar 2023 4:38:06pm
    Author:  程

  ==============================================================================
*/

#include "MiddleRow.h"



MiddleRow::MiddleRow(Week6AssignmentAudioProcessor& inAudioProcessor) :
audioProcessor(inAudioProcessor){
//    startTimerHz(30);
    mDraggableAttackButton.onDrag = [this](){
        sanatizePoints();
    };
    mDraggableDecayButton.onDrag = [this](){
        sanatizePoints();
//        auto& tree_state = audioProcessor.getParameterManager()->getTreeState();
//        mAttack = std::make_unique<SliderContainer>();
//        mAttack->setParameterToControl(tree_state, ParameterIDStrings[AppParameterID::Attack]);
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
    
    juce::Path mResponseCurve;
    juce::Point<float> attackPoint(mDraggableAttackButton.getX() + size / 2.f,
                                   mDraggableAttackButton.getY() + size / 2.f);
    juce::Point<float> decayPoint(mDraggableDecayButton.getX() + size / 2.f,
                                  mDraggableDecayButton.getY() + size / 2.f);
    juce::Point<float> sustainPoint(mDraggableSustainButton.getX() + size / 2.f,
                                    mDraggableSustainButton.getY() + size / 2.f);
    juce::Point<float> releasePoint(mDraggableReleaseButton.getX() + size / 2.f,
                                    mDraggableReleaseButton.getY() + size / 2.f);
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
    updateBounds();
}



void MiddleRow::sanatizePoints()
{
    int x  = juce::jlimit(mDraggableAttackButton.getBounds().getX(),
                         366,
                         mDraggableDecayButton.getBounds().getX());

    int x1 = juce::jlimit(367,
                          733,
                          mDraggableSustainButton.getBounds().getX());

    int x2 = juce::jlimit(734,
                          1100,
                          mDraggableReleaseButton.getBounds().getX());

    mDraggableAttackButton.setTopLeftPosition(0, 301);
    mDraggableDecayButton.setTopLeftPosition(x, 0);
    mDraggableSustainButton.setTopLeftPosition(x1, mDraggableSustainButton.getBounds().getY());
    mDraggableReleaseButton.setTopLeftPosition(x2, 301);


    float attackValue = mDraggableDecayButton.getBounds().getX()/366.f;
    audioProcessor.getParameterManager()->getParameter(Attack, attackValue);

    float decayValue = (mDraggableSustainButton.getBounds().getX() - 367.f)/366.f;
    audioProcessor.getParameterManager()->getParameter(Decay, decayValue);

    float sustainValue = mDraggableSustainButton.getBounds().getY()/301.f;
    audioProcessor.getParameterManager()->getParameter(Sustain, sustainValue);

    float releaseValue = (mDraggableReleaseButton.getBounds().getX()- 734.f)/366.f;
    audioProcessor.getParameterManager()->getParameter(Release, releaseValue);

    repaint();
}

void MiddleRow::updateBounds()
{
    float size = getWidth() / 1000.0f * 20;
    mDraggableAttackButton.setBounds(0, 301, size, size);
    float attackVal = audioProcessor.getParameterManager()->getCurrentParameterValue(Attack);
    float decayVal = audioProcessor.getParameterManager()->getCurrentParameterValue(Decay);
    float sustainVal = audioProcessor.getParameterManager()->getCurrentParameterValue(Sustain);
    float releaseVal = audioProcessor.getParameterManager()->getCurrentParameterValue(Release);
    mDraggableDecayButton.setBounds(juce::jmap (attackVal, 0.f, 366.f), 0, size, size);
    mDraggableSustainButton.setBounds(juce::jmap(decayVal, 367.f, 733.f),
                                      juce::jmap(sustainVal, 301.f, 0.f), size, size);
    mDraggableReleaseButton.setBounds(juce::jmap(releaseVal, 734.f, 1100.f), 301, size, size);
    repaint();
}

//void MiddleRow::timerCallback()
//{
//    updateBounds();
//}
