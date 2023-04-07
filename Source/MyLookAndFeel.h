/*
  ==============================================================================

    LookAndFeel.h
    Created: 18 Mar 2023 3:24:03pm
    Author:  程

  ==============================================================================
*/

#ifndef LookAndFeel_h
#define LookAndFeel_h

#include "JuceHeader.h"

class MyLookAndFeel : public juce::LookAndFeel_V4
{
public:
    
    /* */
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                          float sliderPosProportional, float rotaryStartAngle,
                          float rotaryEndAngle, juce::Slider&) override;
private:
};

#endif 
