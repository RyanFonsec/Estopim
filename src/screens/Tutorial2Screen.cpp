#include "Tutorial2Screen.h"
#include "../assets/screen/Tutorial2_Screen.h"

Tutorial2Screen::Tutorial2Screen(TFT_eSPI* display) {

    tft = display;
}

void Tutorial2Screen::onEnter() {

    tft->fillScreen(TFT_BLACK);
}

void Tutorial2Screen::onExit() {

}

void Tutorial2Screen::update() {

}

GameState Tutorial2Screen::getState() {

    return GameState::TUTORIAL2;
}

void Tutorial2Screen::render() {

    tft->setSwapBytes(true);
    
    tft->pushImage(
        0,
        0,
        320,
        240,
        Tutorial2_Screen
    );

}