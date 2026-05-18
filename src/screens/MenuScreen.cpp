#include "MenuScreen.h"

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

    // FUTURO:
    // Sprite/logo do jogo
    // tft->pushImage(...)

    tft->setTextColor(TFT_RED);

    tft->drawCentreString("ESTOPIM", 160, 30, 4);

    tft->setTextColor(TFT_WHITE);

    tft->drawCentreString("PRESSIONE VERDE", 160, 120, 2);

    tft->drawCentreString("PARA INICIAR", 160, 145, 2);

    tft->drawRect(50, 200, 220, 30, TFT_GREEN);

    tft->drawCentreString("VERDE = START", 160, 208, 2);
}

