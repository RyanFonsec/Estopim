#pragma once

#include <TFT_eSPI.h>

class HUD {

private:

    TFT_eSPI* tft;

    int lives;

    int timeLeft;

    bool livesDirty;

    bool timeDirty;

public:

    HUD(TFT_eSPI* display);

    void setLives(int value);

    void setTime(int value);

    void render();

private:

    void renderLives();

    void renderTime();
};