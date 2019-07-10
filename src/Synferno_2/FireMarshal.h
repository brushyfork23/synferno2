#ifndef FireMarshal_h
#define FireMarshal_h

#include "sequence.h"
#include "Solenoid.h"

// FireMarshal does the actual poofer controlling.
// This object interprets all the various console state
// and turns the solenoids on and off.
class FireMarshal {
    public: 
        // determine new poofer firing states
        void update();

        void clear();

        boolean getFireStateA();
        boolean getFireStateB();
        boolean getFireStateC();
        boolean getFireStateD();

        void setLongDuration(uint8_t ticksPerPoof);
        void setShortDuration(uint8_t ticksPerPoof);
        void setManualAll(boolean pressed);
        void setManualA(boolean pressed);
        void setManualB(boolean pressed);
        void setManualC(boolean pressed);
        void setManualD(boolean pressed);
        void setSequenceTriggers(poof_duration sizeA, poof_duration sizeB, poof_duration sizeC, poof_duration sizeD);
        void tickBeatCounter();

    private:

        Solenoid fireA, fireB, fireC, fireD;
        boolean manualAll, manualA, manualB, manualC, manualD,
            fireStateA, fireStateB, fireStateC, fireStateD;
        poof_duration sequenceSizeA, sequenceSizeB, sequenceSizeC, sequenceSizeD;
        uint8_t longPoofTicks, shortPoofTicks,
            ticksLeftToFireA, ticksLeftToFireB, ticksLeftToFireC, ticksLeftToFireD;
};

#endif