/*
  ==============================================================================

    MiddleRow.cpp
    Created: 18 Mar 2023 4:38:06pm
    Author:  程

  ==============================================================================
*/

#include "MiddleRow.h"

MiddleRow::MiddleRow(ProcessorInterface* inAudioProcessor)
: mProcessorInterface(inAudioProcessor)
{
    startTimerHz(30);
    mDraggableAttackButton.onDrag = [this]() { sanatizePoints(); };
    mDraggableDecayButton.onDrag = [this]() { sanatizePoints(); };
    mDraggableSustainButton.onDrag = [this]() { sanatizePoints(); };
    mDraggableReleaseButton.onDrag = [this]() { sanatizePoints(); };
    addAndMakeVisible(mDraggableAttackButton);
    addAndMakeVisible(mDraggableDecayButton);
    addAndMakeVisible(mDraggableSustainButton);
    addAndMakeVisible(mDraggableReleaseButton);
}

MiddleRow::~MiddleRow() = default;

void MiddleRow::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::hotpink.withBrightness(0.8f));

    g.setColour(juce::Colour(205, 212, 212));
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 0.f);

    float size = static_cast<float>(getWidth()) / 1000.0f * 20;

    juce::Path mResponseCurve;
    juce::Point<float> attackPoint(static_cast<float>(mDraggableAttackButton.getX()) + size / 2.f,
                                   static_cast<float>(mDraggableAttackButton.getY()) + size / 2.f);
    juce::Point<float> decayPoint(static_cast<float>(mDraggableDecayButton.getX()) + size / 2.f,
                                  static_cast<float>(mDraggableDecayButton.getY()) + size / 2.f);
    juce::Point<float> sustainPoint(static_cast<float>(mDraggableSustainButton.getX()) + size / 2.f,
                                    static_cast<float>(mDraggableSustainButton.getY()) + size / 2.f);
    juce::Point<float> releasePoint(static_cast<float>(mDraggableReleaseButton.getX()) + size / 2.f,
                                    static_cast<float>(mDraggableReleaseButton.getY()) + size / 2.f);
    mResponseCurve.startNewSubPath(attackPoint);
    mResponseCurve.lineTo(decayPoint);
    mResponseCurve.startNewSubPath(decayPoint);
    mResponseCurve.lineTo(sustainPoint);
    mResponseCurve.startNewSubPath(sustainPoint);
    mResponseCurve.lineTo(releasePoint);
    g.setColour(juce::Colours::hotpink.withBrightness(0.8f));
    g.strokePath(mResponseCurve, juce::PathStrokeType(5.0f));
}

void MiddleRow::resized()
{
    updateBounds();
}

void MiddleRow::sanatizePoints()
{

    int x = juce::jlimit(mDraggableAttackButton.getBounds().getX(), 366, mDraggableDecayButton.getBounds().getX());

    int x1 = juce::jlimit(367, 733, mDraggableSustainButton.getBounds().getX());

    int x2 = juce::jlimit(734, 1078, mDraggableReleaseButton.getBounds().getX());

    mDraggableAttackButton.setTopLeftPosition(0, 301);
    mDraggableDecayButton.setTopLeftPosition(x, 0);
    mDraggableSustainButton.setTopLeftPosition(x1, mDraggableSustainButton.getBounds().getY());
    mDraggableReleaseButton.setTopLeftPosition(x2, 301);

    float attackValue = static_cast<float>(mDraggableDecayButton.getBounds().getX()) / 366.f;
    mProcessorInterface->getParameterManager()->getParameter(Attack, attackValue);

    float decayValue = (static_cast<float>(mDraggableSustainButton.getBounds().getX()) - 367.f) / 366.f;
    mProcessorInterface->getParameterManager()->getParameter(Decay, decayValue);

    float sustainValue = static_cast<float>(mDraggableSustainButton.getBounds().getY()) / 301.f;
    sustainValue = juce::jmap(sustainValue, 1.f, 0.f);
    mProcessorInterface->getParameterManager()->getParameter(Sustain, sustainValue);

    float releaseValue = (static_cast<float>(mDraggableReleaseButton.getBounds().getX()) - 734.f) / 344.f;
    mProcessorInterface->getParameterManager()->getParameter(Release, releaseValue);

    repaint();
}

void MiddleRow::updateBounds()
{
    auto size = static_cast<float>(static_cast<float>(getWidth()) / 1000.0f * 20);
    mDraggableAttackButton.setBounds(0, 301, static_cast<int>(size), static_cast<int>(size));
    float attackVal = mProcessorInterface->getParameterManager()->getCurrentParameterValue(Attack);
    float decayVal = mProcessorInterface->getParameterManager()->getCurrentParameterValue(Decay);
    float sustainVal = mProcessorInterface->getParameterManager()->getCurrentParameterValue(Sustain);
    float releaseVal = mProcessorInterface->getParameterManager()->getCurrentParameterValue(Release);
    mDraggableDecayButton.setBounds(
        static_cast<int>(juce::jmap(attackVal, 0.f, 366.f)), 0, static_cast<int>(size), static_cast<int>(size));
    mDraggableSustainButton.setBounds(static_cast<int>(juce::jmap(decayVal, 367.f, 733.f)),
                                      static_cast<int>(juce::jmap(sustainVal, 301.f, 0.f)),
                                      static_cast<int>(size),
                                      static_cast<int>(size));
    mDraggableReleaseButton.setBounds(
        static_cast<int>(juce::jmap(releaseVal, 734.f, 1078.f)), 301, static_cast<int>(size), static_cast<int>(size));
    repaint();
}

void MiddleRow::timerCallback()
{
    updateBounds();
}