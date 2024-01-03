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

    auto bounds = juce::Rectangle<float>(static_cast<float>(x),
                                         static_cast<float>(y),
                                         static_cast<float>(width),
                                         static_cast<float>(height)).toFloat().reduced(2);

    auto outlineRadius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.f;
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto lineThickness = outlineRadius * 0.16f;
    auto arcRadius = outlineRadius - lineThickness * 0.5f;

    juce::Path openArc;
    openArc.addCentredArc(bounds.getCentreX(),bounds.getCentreY(),
                          arcRadius,arcRadius,
                          0.0f,
                          rotaryStartAngle,rotaryEndAngle,
                          true);

    g.setColour(outline);
    g.strokePath(openArc, juce::PathStrokeType(lineThickness,
                                               juce::PathStrokeType::curved,
                                               juce::PathStrokeType::rounded));
    if (slider.isEnabled())
    {
        juce::Path valueArc;
        valueArc.addCentredArc(bounds.getCentreX(),bounds.getCentreY(),
                               arcRadius,arcRadius,
                               0.0f,
                               rotaryStartAngle,toAngle,
                               true);

        g.setColour(fill);
        g.strokePath(valueArc, juce::PathStrokeType(lineThickness,
                                                    juce::PathStrokeType::curved,
                                                    juce::PathStrokeType::rounded));
    }

    // draw inner circle
    float innerCircleDiameter = static_cast<float>(juce::jmin(width, height)) * .6f;
    float innerCircleRadius = innerCircleDiameter / 2;
    float rx = static_cast<float>(static_cast<float>(x) + static_cast<float>(width) / 2) - innerCircleRadius;
    float ry = static_cast<float>(static_cast<float>(y) + static_cast<float>(height) / 2) - innerCircleRadius;
    float angle = rotaryStartAngle + (sliderPos * (rotaryEndAngle - rotaryStartAngle));

    juce::Rectangle<float> dialArea(rx, ry, innerCircleDiameter, innerCircleDiameter);

    // draw big circle
    juce::Path dialTick;
    dialTick.addRectangle(0, -innerCircleRadius * 0.95f,
                          innerCircleRadius * 0.15f, innerCircleRadius * 0.3f);


    juce::Colour innerColor = juce::Colours::hotpink;
    if (slider.isMouseOverOrDragging() && slider.isEnabled())
    {
        innerColor = innerColor.brighter();
    }
    g.setColour(innerColor);
    g.fillEllipse(dialArea);

    // draw tick
    g.setColour(juce::Colour(8, 143, 173));
    g.fillPath(dialTick, juce::AffineTransform::rotation(angle).translated(
            static_cast<float>(static_cast<float>(x) + static_cast<float>(width) / 2),
            static_cast<float>(static_cast<float>(y) + static_cast<float>(height) / 2)));
}
