#pragma once

#include <TFT_eSPI.h>

class HUD {

private:

    TFT_eSPI* tft;

    int lives;

    int timeLeft;

    bool livesDirty;

    bool timeDirty;

    const uint16_t* currentBg;

public:

    HUD(TFT_eSPI* display);

    void setLives(int value);

    void setTime(int value);

    void setBackground(const uint16_t* bg);

    void render();

    void forceRedraw();

private:

    void renderLives();

    void renderTimeBar();
};