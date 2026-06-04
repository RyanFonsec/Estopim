#pragma once

#include "MusicSystem.h"

class FeedbackSystem {

private:

    int redPin;
    int greenPin;
    int bluePin;

    int buzzerPin;
    int buzzerChannel;

    unsigned long feedbackStart;

    bool active;

    MusicSystem* music;

public:

    FeedbackSystem(
        MusicSystem* music
    );

    void begin();

    void update();

    void success();

    void error();

    void timeout();

    void clear();
};