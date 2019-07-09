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
    if (this->sequenceSizeA == DURATION_LARGE) this->ticksLeftToFireA = this->largePoofTicks;
    if (this->sequenceSizeB == DURATION_LARGE) this->ticksLeftToFireB = this->largePoofTicks;
    if (this->sequenceSizeC == DURATION_LARGE) this->ticksLeftToFireC = this->largePoofTicks;
    if (this->sequenceSizeD == DURATION_LARGE) this->ticksLeftToFireD = this->largePoofTicks;

    this->fireStateA = this->manualAll || this->manualA || this->ticksLeftToFireA > 0;
    this->fireStateB = this->manualAll || this->manualB || this->ticksLeftToFireB > 0;
    this->fireStateC = this->manualAll || this->manualC || this->ticksLeftToFireC > 0;
    this->fireStateD = this->manualAll || this->manualD || this->ticksLeftToFireD > 0;
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
    return this->manualAll || this->manualA || ticksLeftToFireA > 0;
}

boolean FireMarshal::getFireStateB() {
    return this->manualAll || this->manualB || ticksLeftToFireB > 0;
}

boolean FireMarshal::getFireStateC() {
    return this->manualAll || this->manualC || ticksLeftToFireC > 0;
}

boolean FireMarshal::getFireStateD() {
    return this->manualAll || this->manualD || ticksLeftToFireD > 0;
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