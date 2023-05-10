/*
  ==============================================================================

    LookAndFeel.cpp
    Created: 18 Mar 2023 3:24:03pm
    Author:  程

  ==============================================================================
*/

#include "MyLookAndFeel.h"
//#include "BinaryData.h"
void MyLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                                     float sliderPos, float rotaryStartAngle,
                                     float rotaryEndAngle, juce::Slider& slider)
{
    // draw outline
    auto outline = juce::Colour(8, 143, 173);
    auto fill = slider.findColour(juce::Slider::rotarySliderFillColourId).withBrightness(slider.isEnabled() ? 1.0f : 0.5f);

    auto bounds = juce::Rectangle<float>(x, y, width, height).toFloat().reduced(2);

    auto outlineRadius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.f;
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto lineThickness = outlineRadius * 0.16f;
    auto arcRadius = outlineRadius - lineThickness * 0.5f;

    juce::Path openArc;
    openArc.addCentredArc(bounds.getCentreX(),
                                bounds.getCentreY(),
                                arcRadius,
                                arcRadius,
                                0.0f,
                                rotaryStartAngle,
                                rotaryEndAngle,
                                true);

    g.setColour(outline);
    g.strokePath(openArc, juce::PathStrokeType(lineThickness, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
    if (slider.isEnabled())
    {
        juce::Path valueArc;
        valueArc.addCentredArc(bounds.getCentreX(),
                               bounds.getCentreY(),
                               arcRadius,
                               arcRadius,
                               0.0f,
                               rotaryStartAngle,
                               toAngle,
                               true);

        g.setColour(fill);
        g.strokePath(valueArc, juce::PathStrokeType(lineThickness, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
    }

    // draw inner circle
    float innerCircleDiameter = juce::jmin(width, height) * .6f;
    float innerCircleRadius = innerCircleDiameter / 2;
    float rx = x + width / 2 - innerCircleRadius;
    float ry = y + height / 2 - innerCircleRadius;
    float angle = rotaryStartAngle + (sliderPos * (rotaryEndAngle - rotaryStartAngle));

    juce::Rectangle<float> dialArea(rx, ry, innerCircleDiameter, innerCircleDiameter);

    // draw big circle
    juce::Path dialTick;
    dialTick.addRectangle(0, -innerCircleRadius * 0.95f, innerCircleRadius * 0.15f, innerCircleRadius * 0.3f);


    juce::Colour innerColor = juce::Colours::hotpink;
    if (slider.isMouseOverOrDragging() && slider.isEnabled())
    {
        innerColor = innerColor.brighter();
    }
    g.setColour(innerColor);
    g.fillEllipse(dialArea);
    // draw tick
    g.setColour(juce::Colour(8, 143, 173));
    float thumbWidth = innerCircleDiameter* .1f;
    g.fillPath(dialTick, juce::AffineTransform::rotation(angle).translated(x + width / 2, y + height / 2));
}

//{
//    auto knob_size = juce::jmin(width, height);
//
//    juce::Rectangle<float> container_bounds { (float)x, (float)y, (float)width, (float)height};
//    juce::Rectangle<float> knob_bounds {
//        container_bounds.getCentreX() - knob_size / 2,
//        container_bounds.getCentreY() - knob_size / 2,
//        (float)knob_size,
//        (float)knob_size
//    };
//
//    g.setColour(juce::Colour(8, 143, 173));
//    g.fillEllipse(knob_bounds);
//
//    g.setColour(juce::Colour(255, 255, 255));
//    g.fillEllipse(knob_bounds.reduced(2, 2));
//
//    g.setColour(juce::Colour(8, 143, 173));
//    g.fillEllipse(knob_bounds.reduced(4, 4));
//
//    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
//
//    auto thumbWidth = knob_size * .1;
//
//    auto thumb_radius = knob_size/2 - knob_size *.11;
//
//    juce::Point<float> thumbPoint (knob_bounds.getCentreX() + thumb_radius * std::cos (toAngle -                         juce::MathConstants<float>::halfPi),
//                            knob_bounds.getCentreY() + thumb_radius * std::sin (toAngle -            juce::MathConstants<float>::halfPi));
//
//    g.setColour(juce::Colour(0, 0, 0));
//    g.fillEllipse(juce::Rectangle<float> (thumbWidth, thumbWidth).withCentre (thumbPoint));
//}

//juce::Typeface::Ptr getTypefaceForFont(const juce::Font& f)
//{
//    static juce::Typeface::Ptr myFont = juce::Typeface::createSystemTypefaceFor(BinaryData::Fire_Flight_FREE_ttf, BinaryData::Fire_Flight_FREE_ttfSize);
//    return myFont;
//}