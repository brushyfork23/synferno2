#include "sequence.h"

void Sequence::init() {
    // initialize tick data
    this->populate();
      
    Serial << this->title << F(" sequence minTicksForPriority:") << endl;

    // calculate the minimum ticks between each trigger required
    // to hit all triggers of priority higher-than-or-equal-to each priority level
    for (int p=PRIORITY_LOW; p<=PRIORITY_HIGHEST; p++) {
        // Serial << F("priority: ") << p << endl;
        int minTicks = 0;
        for (int c=0; c<4; c++) {
            // Serial << F("channel: ") << c << endl;
            int8_t lastTick = -1;
            int8_t firstTick = -1; // use this to check the difference between after the last tick until the first tick, wrapping around
            // Serial << F("ticks: ");
            for (int i=0; i<MAX_TICKS; i++) {
                // find the lowest tick difference 
                // Serial << i << F(":");
                if (this->ticks[i] && this->ticks[i]->channel[c].priority >= p) { // this tick has a trigger with the right priority
                    // Serial << this->ticks[i]->channel[c].priority;
                    if (firstTick < 0) {
                        firstTick = i;
                    } else {
                        uint8_t ticksSinceLast = i - lastTick;
                        // Serial << F(":") << ticksSinceLast;
                        if (this->minTicksForPriority[p] < ticksSinceLast) {
                            this->minTicksForPriority[p] = ticksSinceLast;
                        }
                    }
                    lastTick = i;
                } else {
                    // Serial << F(".");
                }
                // Serial << F(" ");
            }
            // Serial << endl;
            // now that we've iterated over all ticks in this channel, additionally check the difference
            // between the final tick and the first tick
            uint8_t ticksFromLastToFirst = MAX_TICKS - lastTick + firstTick;
            // Serial << F("last to first: ") << ticksFromLastToFirst << endl;
            if (this->minTicksForPriority[p] < ticksFromLastToFirst) {
                this->minTicksForPriority[p] = ticksFromLastToFirst;
            }
        }
        Serial << p << F(": ") << this->minTicksForPriority[p] << endl;
    }

}

// given the ticks available between triggers, computed from the current bpm and the duration size,
// set the priority we are capable of rendering
void Sequence::updateViablePriority(uint8_t ticksRequiredForLargePoof) {
    Serial << F("Setting new priority:") << endl;
    Serial << F("ticksRequiredForLargePoof: ") << ticksRequiredForLargePoof << endl;
    Serial << F("PRIORITY_LOW: ") << this->minTicksForPriority[PRIORITY_LOW] << endl;
    Serial << F("PRIORITY_MEDIUM: ") << this->minTicksForPriority[PRIORITY_MEDIUM] << endl;
    Serial << F("PRIORITY_HIGH: ") << this->minTicksForPriority[PRIORITY_HIGH] << endl;
    Serial << F("PRIORITY_HIGHEST: ") << this->minTicksForPriority[PRIORITY_HIGHEST] << endl;
    curPriority = PRIORITY_LOW;
    while (
        curPriority < PRIORITY_HIGHEST
        && this->minTicksForPriority[curPriority] < ticksRequiredForLargePoof
    ) {
        curPriority++;
    }

    Serial << F("final priority: ") << curPriority << endl;
}

// Should we fire now?
TickTriggers Sequence::getTickTriggers(uint8_t tickIndex) {
    Serial << F("tick ") << tickIndex << F(" ");
    poof_duration triggerA = DURATION_NONE;
    poof_duration triggerB = DURATION_NONE;
    poof_duration triggerC = DURATION_NONE;
    poof_duration triggerD = DURATION_NONE;
    // TODO: why is this only returning true for tick 12 for pattern 050?
    if (this->ticks[tickIndex]) {
        Serial << F("curPriority: ") << curPriority << F(" ");
        if (this->ticks[tickIndex]->channel[0].priority >= curPriority) {
            triggerA = this->ticks[tickIndex]->channel[0].duration;
        }
        if (this->ticks[tickIndex]->channel[1].priority >= curPriority) {
            triggerB = this->ticks[tickIndex]->channel[1].duration;
        }
        if (this->ticks[tickIndex]->channel[2].priority >= curPriority) {
            triggerC = this->ticks[tickIndex]->channel[2].duration;
        }
        if (this->ticks[tickIndex]->channel[3].priority >= curPriority) {
            triggerD = this->ticks[tickIndex]->channel[3].duration;
        }
        Serial << F("A ") << this->ticks[tickIndex]->channel[0].priority << F(":") << (this->ticks[tickIndex]->channel[0].priority >= curPriority) << F(":") << triggerA;
        Serial << F(" B ") << this->ticks[tickIndex]->channel[1].priority << F(":") << (this->ticks[tickIndex]->channel[1].priority >= curPriority) << F(":") << triggerB;
        Serial << F(" C ") << this->ticks[tickIndex]->channel[2].priority << F(":") << (this->ticks[tickIndex]->channel[2].priority >= curPriority) << F(":") << triggerC;
        Serial << F(" D ") << this->ticks[tickIndex]->channel[3].priority << F(":") << (this->ticks[tickIndex]->channel[3].priority >= curPriority) << F(":") << triggerD << endl;
    }

    return TickTriggers {
        triggerA,
        triggerB,
        triggerC,
        triggerD
    };

    // return tickTriggers;
}