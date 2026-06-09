#pragma once

class MusicSystem {

private:

    int buzzerPin;
    int channel;

    int currentNote;
    unsigned long noteStart;

    bool paused;

    bool playingEffect;
    unsigned long effectStart;

public:

    MusicSystem();

    void begin();

    void update();

    void pause();

    void resume();

    void playSuccess();

    void playError();

    void playTimeout();

};