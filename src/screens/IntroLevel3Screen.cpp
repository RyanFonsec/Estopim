#include "IntroLevel3Screen.h"

#include "../assets/screen/Intro_Level3_Screen.h"

IntroLevel3Screen::IntroLevel3Screen(TFT_eSPI* display) {

    tft = display;
}

void IntroLevel3Screen::onEnter() {

    tft->fillScreen(TFT_BLACK);
}

void IntroLevel3Screen::onExit() {

}

void IntroLevel3Screen::update() {

}

GameState IntroLevel3Screen::getState() {

    return GameState::INTROLV3;
}

void IntroLevel3Screen::render() {

    tft->setSwapBytes(true);

    tft->pushImage(
        0,
        0,
        320,
        240,
        Intro_Level3_Screen
    );
}