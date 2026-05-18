#pragma once

#include <Arduino.h>

class TimerSystem {

private:

    unsigned long lastTime;

public:

    TimerSystem();

    bool every(unsigned long interval);

};

/*
substitui TODOS os delay()

if(timer.every(1000)) {

   // executa a cada 1 segundo
}*/

