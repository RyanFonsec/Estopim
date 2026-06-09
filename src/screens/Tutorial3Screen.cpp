#include "Tutorial3Screen.h"
#include "../assets/screen/Tutorial3_Screen.h"

Tutorial3Screen::Tutorial3Screen(TFT_eSPI* display) {

    tft = display;
}

void Tutorial3Screen::onEnter() {

    tft->fillScreen(TFT_BLACK);
}

void Tutorial3Screen::onExit() {

}

void Tutorial3Screen::update() {

}

GameState Tutorial3Screen::getState() {

    return GameState::TUTORIAL2;
}

void Tutorial3Screen::render() {

    tft->setSwapBytes(true);
    
    tft->pushImage(
        0,
        0,
        320,
        240,
        Tutorial3_Screen
    );

}