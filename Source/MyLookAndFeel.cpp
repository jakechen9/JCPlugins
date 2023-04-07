/*
  ==============================================================================

    LookAndFeel.cpp
    Created: 18 Mar 2023 3:24:03pm
    Author:  程

  ==============================================================================
*/

#include "MyLookAndFeel.h"
void MyLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                                     float sliderPos, float rotaryStartAngle,
                                     float rotaryEndAngle, juce::Slider& slider)
{
    auto knob_size = juce::jmin(width, height);
    
    juce::Rectangle<float> container_bounds { (float)x, (float)y, (float)width, (float)height};
    juce::Rectangle<float> knob_bounds {
        container_bounds.getCentreX() - knob_size / 2,
        container_bounds.getCentreY() - knob_size / 2,
        (float)knob_size,
        (float)knob_size
    };
    
    g.setColour(juce::Colour(8, 143, 173));
    g.fillEllipse(knob_bounds);
    
    g.setColour(juce::Colour(255, 255, 255));
    g.fillEllipse(knob_bounds.reduced(2, 2));
    
    g.setColour(juce::Colour(8, 143, 173));
    g.fillEllipse(knob_bounds.reduced(4, 4));

    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    
    auto thumbWidth = knob_size * .1;
    
    auto thumb_radius = knob_size/2 - knob_size *.11;
    
    juce::Point<float> thumbPoint (knob_bounds.getCentreX() + thumb_radius * std::cos (toAngle -                         juce::MathConstants<float>::halfPi),
                            knob_bounds.getCentreY() + thumb_radius * std::sin (toAngle -            juce::MathConstants<float>::halfPi));

    g.setColour(juce::Colour(0, 0, 0));
    g.fillEllipse(juce::Rectangle<float> (thumbWidth, thumbWidth).withCentre (thumbPoint));
}
