#include "sequence.h"

void Sequence::init()
{
    // When not initiazlized, sequences should do the least
    for (uint8_t p=PRIORITY_NO; p<N_PRIORITIES; p++) {
        this->minTicksForPriority[p] = MAX_TICKS;
    }

    this->populateTickData();

    this->populateMinimumRequirementsForTriggers();
}

void Sequence::populateMinimumRequirementsForTriggers() {
    // calculate the minimum ticks between each trigger required
    // to hit all triggers of priority higher-than-or-equal-to each priority level
    for (int p=PRIORITY_LOW; p<N_PRIORITIES; p++) {
        for (int c=0; c<4; c++) {
            int8_t lastTick = -1;
            int8_t firstTick = -1; // use this to check the difference between after the last tick until the first tick, wrapping around
            uint8_t minTicksForChannel = MAX_TICKS;
            for (int i=0; i<MAX_TICKS; i++) {
                // find the lowest tick difference 
                if (this->ticks[i] && this->ticks[i]->channel[c].priority >= p) { // this tick has a trigger with the right priority
                    if (firstTick < 0) {
                        firstTick = i;
                    } else {
                        uint8_t ticksSinceLast = i - 1 - lastTick;
                        if (minTicksForChannel > ticksSinceLast) { 
                            minTicksForChannel = ticksSinceLast;
                        }
                    }
                    lastTick = i;
                }
            }
            // now that we've iterated over all ticks in this channel, additionally check the difference
            // between the final tick and the first tick
            uint8_t ticksFromLastToFirst = MAX_TICKS - 1 - lastTick + firstTick;
            if (minTicksForChannel > ticksFromLastToFirst) {
                minTicksForChannel = ticksFromLastToFirst;
            }

            if (this->minTicksForPriority[p] > minTicksForChannel) {
                this->minTicksForPriority[p] = minTicksForChannel;
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
    if (this->ticks[tickIndex]) {
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
    }

    return TickTriggers {
        triggerA,
        triggerB,
        triggerC,
        triggerD
    };
}
