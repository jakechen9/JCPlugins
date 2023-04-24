//
// Created by 程 on 4/24/23.
//

#include "WidthEffect.h"
WidthEffect::WidthEffect()
{

}

WidthEffect::~WidthEffect()
{

}

void WidthEffect::processBlock(float* inBufferL, float* inBufferR, float inWidth, int inNumSamples)
{
    for (int i = 0; i < inNumSamples; ++i) {
        float mid = (inBufferL[i] + inBufferR[i]) / sqrt(2);
        float side = (inBufferL[i] - inBufferR[i]) / sqrt(2);
        mid *= 2.f * (1.f - inWidth);
        side *= 2.f * inWidth;

        inBufferL[i] = (mid + side) / sqrt(2);
        inBufferR[i] = (mid - side) / sqrt(2);
    }
}