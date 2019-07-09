#include "sequence.h"

void Sequence::init()
{
    // When not initiazlized, sequences should do the least
    for (uint8_t p=0; p<N_PRIORITIES; p++) {
        this->minTicksForPriority[p] = MAX_TICKS;
    }
    
    this->populateTickData();

    this->populateMinimumRequirementsForTriggers();
}

void Sequence::populateMinimumRequirementsForTriggers() {
    for (int p=PRIORITY_LOW; p<N_PRIORITIES; p++) {
        int8_t lastTickForChannel[4] = {-1,-1,-1,-1};
        int8_t firstTickForChannel[4] = {-1,-1,-1,-1}; // use this to check the difference between after the last tick until the first tick, wrapping around
        uint8_t minTicksRequiredForChannel[4] = {MAX_TICKS, MAX_TICKS, MAX_TICKS, MAX_TICKS};
        for (int i=0; i<MAX_TICKS; i++) {
            if (this->priorities[p].ticks[i]) {
                for (int c=0; c<4; c++) {
                    if (this->priorities[p].ticks[i]->channels[c] > DURATION_NONE) {
                        if (firstTickForChannel[c] < 0) {
                            firstTickForChannel[c] = i;
                        } else {
                            uint8_t ticksSinceLast = i - 1 - firstTickForChannel[c];
                            if (minTicksRequiredForChannel[c] > ticksSinceLast) { 
                                minTicksRequiredForChannel[c] = ticksSinceLast;
                            }
                        }
                        lastTickForChannel[c] = i;
                    }
                }
            }
        }

        // now that we've iterated over all ticks, additionally check the difference
        // between the final ticks and the first ticks for each channel
        for (int c=0; c<4; c++) {
            uint8_t ticksFromLastToFirst = MAX_TICKS - 1 - lastTickForChannel[c] + firstTickForChannel[c];
            if (minTicksRequiredForChannel[c] > ticksFromLastToFirst) {
                minTicksRequiredForChannel[c] = ticksFromLastToFirst;
            }
        }

        // find the strictest requirement amongst all the channels
        for (int c=0; c<4; c++) {
            if (this->minTicksForPriority[p] > minTicksRequiredForChannel[c]) {
                this->minTicksForPriority[p] = minTicksRequiredForChannel[c];
            }
        }
    }
}

// given the ticks available between triggers, computed from the current bpm and the duration size,
// set the priority we are capable of rendering
void Sequence::updateViablePriority(uint8_t ticksRequiredForLargePoof) {
    curPriority = PRIORITY_LOW;
    while (
        curPriority < PRIORITY_HIGH
        && this->minTicksForPriority[curPriority] < ticksRequiredForLargePoof
    ) {
        curPriority++;
    }
}

// Should we fire now?
TickTriggers Sequence::getTickTriggers(uint8_t tickIndex) {
    poof_duration triggerA = DURATION_NONE;
    poof_duration triggerB = DURATION_NONE;
    poof_duration triggerC = DURATION_NONE;
    poof_duration triggerD = DURATION_NONE;
    if (this->priorities[curPriority].ticks[tickIndex]) {
        triggerA = this->priorities[curPriority].ticks[tickIndex]->channels[0];
        triggerB = this->priorities[curPriority].ticks[tickIndex]->channels[1];
        triggerC = this->priorities[curPriority].ticks[tickIndex]->channels[2];
        triggerD = this->priorities[curPriority].ticks[tickIndex]->channels[3];
    }

    return TickTriggers {
        triggerA,
        triggerB,
        triggerC,
        triggerD
    };
}
