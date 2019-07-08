#include "fireMarshal.h"

void FireMarshal::tick() {
    if (this->sequenceSizeA == DURATION_LARGE) {
        ticksLeftToFireA = this->largePoofTicks;
    }
    if (this->sequenceSizeB == DURATION_LARGE) {
        ticksLeftToFireB = this->largePoofTicks;
    }
    if (this->sequenceSizeC == DURATION_LARGE) {
        ticksLeftToFireC = this->largePoofTicks;
    }
    if (this->sequenceSizeD == DURATION_LARGE) {
        ticksLeftToFireD = this->largePoofTicks;
    }

    this->fireStateA = this->manualAll || this->manualA || ticksLeftToFireA > 0;
    this->fireStateB = this->manualAll || this->manualB || ticksLeftToFireB > 0;
    this->fireStateC = this->manualAll || this->manualC || ticksLeftToFireC > 0;
    this->fireStateD = this->manualAll || this->manualD || ticksLeftToFireD > 0;

    if (ticksLeftToFireA > 0) ticksLeftToFireA--;
    if (ticksLeftToFireB > 0) ticksLeftToFireB--;
    if (ticksLeftToFireC > 0) ticksLeftToFireC--;
    if (ticksLeftToFireD > 0) ticksLeftToFireD--;
}

boolean FireMarshal::getFireStateA() {
    return this->fireStateA;
}

boolean FireMarshal::getFireStateB() {
    return this->fireStateB;
}

boolean FireMarshal::getFireStateC() {
    return this->fireStateC;
}

boolean FireMarshal::getFireStateD() {
    return this->fireStateD;
}

void FireMarshal::setDuration(uint8_t ticksPerPoof) {
    this->largePoofTicks = ticksPerPoof;
}

void FireMarshal::setManualAll(boolean pressed) {
    this->manualAll = pressed;
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