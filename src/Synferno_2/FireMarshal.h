#ifndef FireMarshal_h
#define FireMarshal_h

#include "sequence.h"
#include "Solenoid.h"

// FireMarshal does the actual poofer controlling.
// This object interprets all the various console state
// and turns the solenoids on and off.
class FireMarshal {
    public: 
        // tick the clock counter and determine new poofer firing states
        void tick();

        boolean getFireStateA();
        boolean getFireStateB();
        boolean getFireStateC();
        boolean getFireStateD();

        void setDuration(uint8_t ticksPerPoof);
        void setManualAll(boolean pressed);
        void setManualA(boolean pressed);
        void setManualB(boolean pressed);
        void setManualC(boolean pressed);
        void setManualD(boolean pressed);
        void setSequenceTriggers(poof_duration sizeA, poof_duration sizeB, poof_duration sizeC, poof_duration sizeD);

    private:

        Solenoid fireA, fireB, fireC, fireD;
        boolean manualAll, manualA, manualB, manualC, manualD,
            fireStateA, fireStateB, fireStateC, fireStateD;
        poof_duration sequenceSizeA, sequenceSizeB, sequenceSizeC, sequenceSizeD;
        uint8_t largePoofTicks,
            ticksLeftToFireA, ticksLeftToFireB, ticksLeftToFireC, ticksLeftToFireD;
};

#endif