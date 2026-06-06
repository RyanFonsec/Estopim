#pragma once

enum class MusicMode {
    EXPLORATION,
    BATTLE
};

class MusicSystem {

private:

    MusicMode currentMode;

    int buzzerPin;
    int channel;

    int currentNote;
    unsigned long noteStart;

    bool paused;

    bool playingEffect;
    unsigned long effectStart;

public:

    MusicSystem();

    void setMode(MusicMode mode);

    void begin();

    void update();

    void pause();

    void resume();

    void playSuccess();

    void playError();

    void playTimeout();

};