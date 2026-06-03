#include "IntroLevel1Screen.h"

#include "../assets/screen/Intro_Level1_Screen.h"

IntroLevel1Screen::IntroLevel1Screen(TFT_eSPI* display) {

    tft = display;
}

void IntroLevel1Screen::onEnter() {

    tft->fillScreen(TFT_BLACK);
}

void IntroLevel1Screen::onExit() {

}

void IntroLevel1Screen::update() {

}

GameState IntroLevel1Screen::getState() {

    return GameState::INTROLV1;
}

void IntroLevel1Screen::render() {

    /*tft->setSwapBytes(true);

    tft->pushImage(
        0,
        0,
        320,
        240,
        Intro_Level1_Screen
    );*/
}