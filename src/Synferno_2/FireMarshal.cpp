#include "fireMarshal.h"

void FireMarshal::clear() {
    this->sequenceSizeA = 0;
    this->sequenceSizeB = 0;
    this->sequenceSizeC = 0;
    this->sequenceSizeD = 0;
    this->ticksLeftToFireA = 0;
    this->ticksLeftToFireB = 0;
    this->ticksLeftToFireC = 0;
    this->ticksLeftToFireD = 0;
}

void FireMarshal::update() {
    if (this->sequenceSizeA == DURATION_LONG) {
        this->ticksLeftToFireA = this->longPoofTicks;
    } else if (this->sequenceSizeA == DURATION_SHORT) {
         this->ticksLeftToFireA = this->shortPoofTicks;
    }
    if (this->sequenceSizeB == DURATION_LONG) {
        this->ticksLeftToFireB = this->longPoofTicks;
    } else if (this->sequenceSizeB == DURATION_SHORT) {
         this->ticksLeftToFireB = this->shortPoofTicks;
    }
    if (this->sequenceSizeC == DURATION_LONG) {
        this->ticksLeftToFireC = this->longPoofTicks;
    } else if (this->sequenceSizeC == DURATION_SHORT) {
         this->ticksLeftToFireC = this->shortPoofTicks;
    }
    if (this->sequenceSizeD == DURATION_LONG) {
        this->ticksLeftToFireD = this->longPoofTicks;
    } else if (this->sequenceSizeD == DURATION_SHORT) {
         this->ticksLeftToFireD = this->shortPoofTicks;
    }

    this->fireStateA = this->manualAll || (this->manualAllAltEnabled && this->manualAllAlt) || this->manualA || this->ticksLeftToFireA > 0;
    this->fireStateB = this->manualAll || (this->manualAllAltEnabled && this->manualAllAlt) || this->manualB || this->ticksLeftToFireB > 0;
    this->fireStateC = this->manualAll || (this->manualAllAltEnabled && this->manualAllAlt) || this->manualC || this->ticksLeftToFireC > 0;
    this->fireStateD = this->manualAll || (this->manualAllAltEnabled && this->manualAllAlt) || this->manualD || this->ticksLeftToFireD > 0;
}

void FireMarshal::tickBeatCounter() {
    if (this->ticksLeftToFireA > 0) {
        this->ticksLeftToFireA--;
    }
    if (this->ticksLeftToFireB > 0) {
        this->ticksLeftToFireB--;
    }
    if (this->ticksLeftToFireC > 0) {
        this->ticksLeftToFireC--;
    }
    if (this->ticksLeftToFireD > 0) {
        this->ticksLeftToFireD--;
    }
}

boolean FireMarshal::getFireStateA() {
    return this->manualAll || (this->manualAllAltEnabled && this->manualAllAlt) || this->manualA || ticksLeftToFireA > 0;
}

boolean FireMarshal::getFireStateB() {
    return this->manualAll || (this->manualAllAltEnabled && this->manualAllAlt) || this->manualB || ticksLeftToFireB > 0;
}

boolean FireMarshal::getFireStateC() {
    return this->manualAll || (this->manualAllAltEnabled && this->manualAllAlt) || this->manualC || ticksLeftToFireC > 0;
}

boolean FireMarshal::getFireStateD() {
    return this->manualAll || (this->manualAllAltEnabled && this->manualAllAlt) || this->manualD || ticksLeftToFireD > 0;
}

void FireMarshal::setLongDuration(uint8_t ticksPerPoof) {
    this->longPoofTicks = ticksPerPoof;
}

void FireMarshal::setShortDuration(uint8_t ticksPerPoof) {
    this->shortPoofTicks = ticksPerPoof;
}

void FireMarshal::setManualAll(boolean pressed) {
    this->manualAll = pressed;
}
void FireMarshal::setManualAllAlt(boolean pressed) {
    this->manualAllAlt = pressed;
}
void FireMarshal::setManualAllAltEnabled(boolean enabled) {
    this->manualAllAltEnabled = enabled;
}
void FireMarshal::setManualA(boolean pressed) {
    this->manualA = pressed;
}
void FireMarshal::setManualB(boolean pressed) {
    this->manualB = pressed;
}
void FireMarshal::setManualC(boolean pressed) {
    this->manualC = pressed;
}
void FireMarshal::setManualD(boolean pressed) {
    this->manualD = pressed;
}
void FireMarshal::setSequenceTriggers(poof_duration sizeA, poof_duration sizeB, poof_duration sizeC, poof_duration sizeD) {
    this->sequenceSizeA = sizeA;
    this->sequenceSizeB = sizeB;
    this->sequenceSizeC = sizeC;
    this->sequenceSizeD = sizeD;
}