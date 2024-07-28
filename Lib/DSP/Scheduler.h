/*
  ==============================================================================

    Scheduler.h
    Created: 10 Apr 2023 9:21:19pm
    Author:  程

  ==============================================================================
*/
#ifndef Scheduler_h
#define Scheduler_h

class Scheduler
{
public:

    void setTime(float inTimeSamples)
    {
        mTimeInSamples = static_cast<int>(inTimeSamples);
    }

    bool trigger()
    {
        auto res = mCounter == 0;

        mCounter++;

        if (mCounter >= mTimeInSamples) {
            mCounter = 0;
        }

        return res;
    }

    void reset()
    {
        mCounter = 0;
    }

private:

    int mCounter = 0;
    int mTimeInSamples = 0;
};

#endif /* Scheduler_h */
