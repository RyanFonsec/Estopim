#include "HUD.h"

HUD::HUD(TFT_eSPI* display) {

    tft = display;

    lives = -1;

    timeLeft = -1;

    livesDirty = true;

    timeDirty = true;
}

void HUD::setLives(int value) {

    if(lives != value) {

        lives = value;

        livesDirty = true;
    }
}


void HUD::setTime(int value) {

    if(timeLeft != value) {

        timeLeft = value;

        timeDirty = true;
    }
}

void HUD::render() {

    renderLives();

    renderTime();
}

void HUD::renderLives() {

    if(!livesDirty) {

        return;
    }

    tft->fillRect(0, 0, 80, 30, TFT_BLACK);

    tft->setTextColor(TFT_RED);

    tft->drawString(
        "HP: " + String(lives),
        5,
        5,
        2
    );

    livesDirty = false;
}

void HUD::renderTime() {

    if(!timeDirty) {

        return;
    }

    // LIMPA SÓ ÁREA DO TEMPO

    tft->fillRect(240, 0, 80, 30, TFT_BLACK);

    tft->setTextColor(TFT_GREEN);

    tft->drawRightString(
        String(timeLeft),
        310,
        5,
        2
    );

    timeDirty = false;
}