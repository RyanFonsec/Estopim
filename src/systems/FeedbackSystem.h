#pragma once

class FeedbackSystem {

private:

    int redPin;

    int greenPin;

    int bluePin;

    int buzzerPin;

    int buzzerChannel;

public:

    FeedbackSystem();

    void begin();

    void success();

    void error();

    void timeout();

    void clear();
};