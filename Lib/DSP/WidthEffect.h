//
// Created by 程 on 4/24/23.
//

#ifndef JCFINALDELAY_WIDTHEFFECT_H
#define JCFINALDELAY_WIDTHEFFECT_H

#include "JuceHeader.h"
class WidthEffect
{
public:
    WidthEffect();
    ~WidthEffect();

    static void processBlock(float* inBufferL, float* inBufferR, float inWidth, int inNumSamples);

private:

};




#endif //JCFINALDELAY_WIDTHEFFECT_H
