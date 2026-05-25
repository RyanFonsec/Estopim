#include "TimerSystem.h"

TimerSystem::TimerSystem() {

    lastTime = 0;
}

bool TimerSystem::every(unsigned long interval) {

    unsigned long now = millis();

    if(now - lastTime >= interval) {

        lastTime = now;

        return true;
    }

    return false;
}

