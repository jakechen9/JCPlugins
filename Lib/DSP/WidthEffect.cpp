//
// Created by 程 on 4/24/23.
//

#include "WidthEffect.h"
WidthEffect::WidthEffect()
= default;

WidthEffect::~WidthEffect()
= default;

void WidthEffect::processBlock(float* inBufferL, float* inBufferR, float inWidth, int inNumSamples)
{
    for (int i = 0; i < inNumSamples; ++i) {
        auto mid = static_cast<float>((inBufferL[i] + inBufferR[i]) / sqrt(2));
        auto side = static_cast<float>((inBufferL[i] - inBufferR[i]) / sqrt(2));

        mid *= 2.f * (1.f - inWidth);
        side *= 2.f * inWidth;

        inBufferL[i] = static_cast<float>((mid + side) / sqrt(2));
        inBufferR[i] = static_cast<float>((mid - side) / sqrt(2));
    }
}