#pragma once

class FeedbackSystem {

private:

    int redPin;

    int greenPin;

    int bluePin;

    int buzzerPin;

    int buzzerChannel;

    unsigned long feedbackStart;

    bool active;

public:

    FeedbackSystem();

    void begin();

    void update();

    void success();

    void error();

    void timeout();

    void clear();
};