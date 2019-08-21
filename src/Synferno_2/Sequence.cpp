#include "sequence.h"

void Sequence::init()
{
    // When not initiazlized, sequences should do the least
    for (uint8_t p=0; p<N_PRIORITIES; p++) {
        this->ticksRequiredForAllLongPoofs[p] = MAX_TICKS;
        this->ticksRequiredForAllShortPoofs[p] = MAX_TICKS;
    }
    
    this->populateTickData();

    this->populateMinimumRequirementsForTriggers();

    this->determinePopulatedPriorities();
}

void Sequence::determinePopulatedPriorities() {
    uint8_t p = PRIORITY_LOW;
    uint8_t i = 0;
    while(!this->priorities[p].ticks[i]) {
        i++;
        if (i >= MAX_TICKS) {
            i = 0;
            p++;
        }
    }
    this->lowestPopulatedPriority = p;

    i = MAX_TICKS - 1;
    p = PRIORITY_HIGH;
    while(!this->priorities[p].ticks[i]) {
        if (i == 0) {
            i = MAX_TICKS - 1;
            p--;
        } else {
            i--;
        }
    }
    this->highestPopulatedPriority = p;
}

void Sequence::populateMinimumRequirementsForTriggers() {
    for (uint8_t p=PRIORITY_LOW; p<N_PRIORITIES; p++) {
        int8_t lastTickForChannel[4] = {-1,-1,-1,-1};
        int8_t firstTickForChannel[4] = {-1,-1,-1,-1}; // use this to check the difference between after the last tick until the first tick, wrapping around
        poof_duration lastTickSizeForChannel[4] = {DURATION_NONE,DURATION_NONE,DURATION_NONE,DURATION_NONE};
        uint8_t minTicksRequiredForLongPoofForChannel[4] = {MAX_TICKS, MAX_TICKS, MAX_TICKS, MAX_TICKS};
        uint8_t minTicksRequiredForShortPoofForChannel[4] = {MAX_TICKS, MAX_TICKS, MAX_TICKS, MAX_TICKS};
        for (uint8_t i=0; i<MAX_TICKS; i++) {
            if (this->priorities[p].ticks[i]) {
                for (uint8_t c=0; c<4; c++) {
                    if (this->priorities[p].ticks[i]->channels[c] > DURATION_NONE) {
                        if (firstTickForChannel[c] < 0) {
                            firstTickForChannel[c] = i;
                        } else {
                            uint8_t ticksSinceLast = i - 1 - firstTickForChannel[c];
                            if (lastTickSizeForChannel[c] == DURATION_LONG) {
                                if (minTicksRequiredForLongPoofForChannel[c] > ticksSinceLast) { 
                                    minTicksRequiredForLongPoofForChannel[c] = ticksSinceLast;
                                }
                            } else {
                                if (minTicksRequiredForShortPoofForChannel[c] > ticksSinceLast) { 
                                    minTicksRequiredForShortPoofForChannel[c] = ticksSinceLast;
                                }
                            }
                        }
                        lastTickForChannel[c] = i;
                        lastTickSizeForChannel[c] = this->priorities[p].ticks[i]->channels[c];
                    }
                }
            }
        }

        // now that we've iterated over all ticks, additionally check the difference
        // between the final ticks and the first ticks for each channel
        for (uint8_t c=0; c<4; c++) {
            uint8_t ticksFromLastToFirst = MAX_TICKS - 1 - lastTickForChannel[c] + firstTickForChannel[c];
            if (lastTickSizeForChannel[c] == DURATION_LONG && minTicksRequiredForLongPoofForChannel[c] > ticksFromLastToFirst) {
                minTicksRequiredForLongPoofForChannel[c] = ticksFromLastToFirst;
            } else if (lastTickSizeForChannel[c] == DURATION_SHORT && minTicksRequiredForShortPoofForChannel[c] > ticksFromLastToFirst) {
                minTicksRequiredForShortPoofForChannel[c] = ticksFromLastToFirst;
            }
        }

        // find the strictest requirement amongst all the channels
        for (uint8_t c=0; c<4; c++) {
            if (this->ticksRequiredForAllLongPoofs[p] > minTicksRequiredForLongPoofForChannel[c]) {
                this->ticksRequiredForAllLongPoofs[p] = minTicksRequiredForLongPoofForChannel[c];
            }
            if (this->ticksRequiredForAllShortPoofs[p] > minTicksRequiredForShortPoofForChannel[c]) {
                this->ticksRequiredForAllShortPoofs[p] = minTicksRequiredForShortPoofForChannel[c];
            }
        }
    }
}

// given the ticks available between triggers, computed from the current bpm and the duration size,
// set the priority we are capable of rendering
void Sequence::updateViablePriority(uint8_t ticksPerLongPoof, uint8_t ticksPerShortPoof) {
    this->minViablePriority = PRIORITY_LOW;
    while (
        this->minViablePriority < PRIORITY_HIGH
        && (
            this->ticksRequiredForAllLongPoofs[this->minViablePriority] < ticksPerLongPoof
            || this->ticksRequiredForAllShortPoofs[this->minViablePriority] < ticksPerShortPoof
        )
    ) {
        this->minViablePriority++;
    }
}

// Should we fire now?
TickTriggers Sequence::getTickTriggers(uint8_t tickIndex, trigger_priority min, trigger_priority max) {
    poof_duration triggerA = DURATION_NONE;
    poof_duration triggerB = DURATION_NONE;
    poof_duration triggerC = DURATION_NONE;
    poof_duration triggerD = DURATION_NONE;

    trigger_priority p = this->minViablePriority;
    if (min > p) {
        p = min;
    }
    if (p < this->lowestPopulatedPriority) {
        p = this->lowestPopulatedPriority;
    }
    if (max < p) {
        p = max;
    }
    if (p > this->highestPopulatedPriority) {
        p = this->highestPopulatedPriority;
    }

    // if there are no triggers for this prirotiy (like maybe we only set
    // stuff for MEDIUM but now we're in HIGH), move to a priority we _do_ have.
    //this->ticksRequiredForAllLongPoofs

    if (this->priorities[p].ticks[tickIndex]) {
        triggerA = this->priorities[p].ticks[tickIndex]->channels[0];
        triggerB = this->priorities[p].ticks[tickIndex]->channels[1];
        triggerC = this->priorities[p].ticks[tickIndex]->channels[2];
        triggerD = this->priorities[p].ticks[tickIndex]->channels[3];
    }

    return TickTriggers {
        triggerA,
        triggerB,
        triggerC,
        triggerD
    };
}