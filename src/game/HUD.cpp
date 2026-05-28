#include "HUD.h"

#include "../assets/hud/heart_icon.h"
#include "../assets/hud/player_icon.h"
#include "../assets/backgrounds/level1_bg.h"

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

    renderTimeBar();
}

void HUD::renderLives() {

    if(!livesDirty) {

        return;
    }

        tft->pushImage(
        0,
        0,
        90,
        17,
        level1_bg
    );

    tft->pushImage(
        5,
        2,
        24,
        24,
        player_icon,
        TFT_BLACK
    );

    for(int i = 0; i < lives; i++) {

        tft->pushImage(
            35 + (i * 18),
            5,
            16,
            16,
            heart_icon,
            TFT_BLACK
        );
    }

    livesDirty = false;
}

void HUD::renderTimeBar() {

    if(!timeDirty) {

        return;
    }



    // ============================================
    // TEXTO TEMPO
    // ============================================

    tft->setTextColor(TFT_WHITE);

    tft->drawRightString(
        String(timeLeft) + " SEG",
        310,
        138,
        2
    );

    // ============================================
    // BORDA BARRA
    // ============================================

    tft->drawRect(
        10,
        140,
        220,
        10,
        TFT_WHITE
    );

    // ============================================
    // TAMANHO BARRA
    // ============================================

    int width = map(
        timeLeft,
        0,
        15,
        0,
        216
    );

    // ============================================
    // BARRA VERDE
    // ============================================

    tft->fillRect(
        12,
        142,
        width,
        6,
        TFT_GREEN
    );

    timeDirty = false;
}