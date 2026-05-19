#pragma once

#include <TFT_eSPI.h>

class HUD {

private:

    TFT_eSPI* tft;

    int lives;

    int score;

    int timeLeft;

    int lastLives;

    int lastScore;

    int lastTime;
public:

    HUD(TFT_eSPI* display);

    void setLives(int value);

    void setScore(int value);

    void setTime(int value);

    void render();

};