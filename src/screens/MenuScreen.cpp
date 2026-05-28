#include "MenuScreen.h"
#include "../assets/screen/menu_bg.h"


MenuScreen::MenuScreen(TFT_eSPI* display) {

    tft = display;
}

void MenuScreen::onEnter() {

    tft->fillScreen(TFT_BLACK);
}

void MenuScreen::onExit() {

}

void MenuScreen::update() {

}

GameState MenuScreen::getState() {

    return GameState::MENU;
}

void MenuScreen::render() {

    tft->fillScreen(TFT_BLACK);

    tft->setSwapBytes(true);

    tft->pushImage(
        0,
        0,
        320,
        240,
        menu_bg
    );
}
