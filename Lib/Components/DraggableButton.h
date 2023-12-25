/*
  ==============================================================================

    DraggableButton.h
    Created: 8 Apr 2023 9:21:19pm
    Author:  程

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class DraggableButton : public juce::Component,
                        public juce::DragAndDropContainer,
                        public juce::ComponentDragger,
                        public juce::ComponentBoundsConstrainer
{
public:
    DraggableButton();
    ~DraggableButton() override;
    
    void paint(juce::Graphics& g) override;
    void resized() override;
    void mouseDown (const juce::MouseEvent& e) override;
    void mouseDrag (const juce::MouseEvent& e) override;
    void mouseEnter(const juce::MouseEvent& event) override;
    void mouseExit(const juce::MouseEvent& event) override;

    std::function<void()> onDrag;
    void setState(bool state);
    
private:
    bool isEntered = false;
    juce::Colour getColour() const;
    bool mState = true;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DraggableButton)
};
