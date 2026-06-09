#include "IntroLevel2Screen.h"

#include "../assets/screen/Intro_Level2_Screen.h"

IntroLevel2Screen::IntroLevel2Screen(TFT_eSPI* display) {

    tft = display;
}

void IntroLevel2Screen::onEnter() {

    tft->fillScreen(TFT_BLACK);
}

void IntroLevel2Screen::onExit() {

}

void IntroLevel2Screen::update() {

}

GameState IntroLevel2Screen::getState() {

    return GameState::INTROLV1;
}

void IntroLevel2Screen::render() {
    tft->setSwapBytes(true);
/*
    tft->pushImage(
        0,
        0,
        320,
        240,
        Intro_Level2_Screen
    );*/
}