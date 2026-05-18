#include "WinScreen.h"

WinScreen::WinScreen(TFT_eSPI* display) {

    tft = display;
}

void WinScreen::onEnter() {

    tft->fillScreen(TFT_BLACK);
}

void WinScreen::onExit() {

}

void WinScreen::update() {

}

GameState WinScreen::getState() {

    return GameState::WIN;
}

void WinScreen::render() {

    tft->fillScreen(TFT_GREEN);

    // FUTURO:
    // Sprite de vitória

    tft->setTextColor(TFT_BLACK);

    tft->drawCentreString("VOCE VENCEU!", 160, 100, 4);

    tft->drawCentreString("SALVADOR FOI SALVA", 160, 150, 2);
}
