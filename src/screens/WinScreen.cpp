#include "WinScreen.h"
#include "../assets/screen/win_screen.h"

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

    tft->fillScreen(TFT_BLACK);

    tft->setSwapBytes(true);
    
    tft->pushImage(
        0,
        0,
        320,
        240,
        win_screen
    );
}
