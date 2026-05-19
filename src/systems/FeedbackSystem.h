#pragma once

class FeedbackSystem {

private:

    int ledPin;

    int buzzerPin;

public:

    FeedbackSystem();

    void begin();

    void success();

    void error();

    void timeout();
};