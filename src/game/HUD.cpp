#include "HUD.h"
#include "../assets/hud/heart_icon.h"
#include "../assets/hud/player_icon.h"
#include "../systems/BgUtils.h"

HUD::HUD(TFT_eSPI* display) {
    tft       = display;
    currentBg = nullptr;
    lives     = -1;
    timeLeft  = -1;
    livesDirty = true;
    timeDirty  = true;
}

void HUD::setLives(int value) {
    if (lives != value) { lives = value; livesDirty = true; }
}

void HUD::setTime(int value) {
    if (timeLeft != value) { timeLeft = value; timeDirty = true; }
}

void HUD::setBackground(const uint16_t* bg) {
    currentBg = bg;
}

void HUD::render() {
    renderLives();
    renderTimeBar();
}

void HUD::renderLives() {
    if (!livesDirty) return;
    if (!currentBg)  return;

    BgUtils::restore(tft, currentBg, 0, 0, 120, 30);

    tft->pushImage(5, 2, 24, 24, (uint16_t*)player_icon, TFT_BLACK);

    for (int i = 0; i < lives; i++) {
        tft->pushImage(35 + (i * 18), 5, 16, 16,
                       (uint16_t*)heart_icon, TFT_BLACK);
    }

    livesDirty = false;
}

void HUD::renderTimeBar() {
    if (!timeDirty) return;
    if (!currentBg) return;

    BgUtils::restore(
        tft, 
        currentBg, 
        0, 
        130, 
        320, 
        30
    );

    tft->setTextColor(TFT_WHITE);

    tft->drawRightString(
     String(timeLeft) + " SEG",
     305,
     145,
     2
    );

    tft->drawRect(10, 146, 220, 10, TFT_WHITE);

    int width = map(timeLeft, 0, 15, 0, 216);
    if (width < 0) width = 0;
    if (width > 0) tft->fillRect(12, 148, width, 6, TFT_GREEN);

    timeDirty = false;
}