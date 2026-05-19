#include "HUD.h"

HUD::HUD(TFT_eSPI* display) {

    tft = display;

    lives = 3;

    score = 0;

    timeLeft = 15;

    lastLives = -1;
    lastScore = -1;
    lastTime = -1;
}

void HUD::setLives(int value) {

    lives = value;
}

void HUD::setScore(int value) {

    score = value;
}

void HUD::setTime(int value) {

    timeLeft = value;
}

void HUD::render() {

    tft->setTextColor(TFT_WHITE);

    // =========================
    // VIDAS
    // =========================

    if(lives != lastLives) {

        tft->fillRect(0, 0, 90, 30, TFT_BLACK);

        tft->drawString(
            "VIDAS: " + String(lives),
            5,
            5,
            2
        );

        lastLives = lives;
    }

    // =========================
    // SCORE
    // =========================

    if(score != lastScore) {

        tft->fillRect(95, 0, 120, 30, TFT_BLACK);

        tft->drawString(
            "PONTOS: " + String(score),
            100,
            5,
            2
        );

        lastScore = score;
    }

    // =========================
    // TEMPO
    // =========================

    if(timeLeft != lastTime) {

        tft->fillRect(220, 0, 100, 30, TFT_BLACK);

        tft->drawString(
            "TEMPO: " + String(timeLeft),
            225,
            5,
            2
        );

        lastTime = timeLeft;
    }
}