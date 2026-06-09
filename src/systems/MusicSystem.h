#pragma once

enum class MusicMode {
    EXPLORATION,
    BATTLE
};

enum class EffectType {

    NONE,

    SUCCESS,

    ERROR,

    TIMEOUT
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

    EffectType currentEffect;

    int effectStep;

    unsigned long effectTimer;

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