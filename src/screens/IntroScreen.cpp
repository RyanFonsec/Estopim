#include "IntroScreen.h"
#include "../assets/screen/Intro_screen.h"

IntroScreen::IntroScreen(TFT_eSPI* display) {

    tft = display;
}

void IntroScreen::onEnter() {

    tft->fillScreen(TFT_BLACK);
}

void IntroScreen::onExit() {

}

void IntroScreen::update() {

}

GameState IntroScreen::getState() {

    return GameState::INTRO;
}

void IntroScreen::render() {

    tft->setSwapBytes(true);
   /* 
    tft->pushImage(
        0,
        0,
        320,
        240,
        Intro_screen
    );*/

}