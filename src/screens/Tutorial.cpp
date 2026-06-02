#include "TutorialScreen.h"
#include "../assets/screen/Tutorial_Screen.h"

TutorialScreen::TutorialScreen(TFT_eSPI* display) {

    tft = display;
}

void TutorialScreen::onEnter() {

    tft->fillScreen(TFT_BLACK);
}

void TutorialScreen::onExit() {

}

void TutorialScreen::update() {

}

GameState TutorialScreen::getState() {

    return GameState::TUTORIAL;
}

void TutorialScreen::render() {

    tft->setSwapBytes(true);
    
    tft->pushImage(
        0,
        0,
        320,
        240,
        Tutorial_Screen
    );

}