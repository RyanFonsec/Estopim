#include "IntroLevel4Screen.h"

#include "../assets/screen/Intro_Level4_Screen.h"

IntroLevel4Screen::IntroLevel4Screen(TFT_eSPI* display) {

    tft = display;
}

void IntroLevel4Screen::onEnter() {

    tft->fillScreen(TFT_BLACK);
}

void IntroLevel4Screen::onExit() {

}

void IntroLevel4Screen::update() {

}

GameState IntroLevel4Screen::getState() {

    return GameState::INTROLV4;
}

void IntroLevel4Screen::render() {

    tft->setSwapBytes(true);

    tft->pushImage(
        0,
        0,
        320,
        240,
        Intro_Level4_Screen
    );
}