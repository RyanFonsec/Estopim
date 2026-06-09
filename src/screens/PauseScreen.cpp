#include "PauseScreen.h"

PauseScreen::PauseScreen(TFT_eSPI* display) {

    tft = display;
}

void PauseScreen::onEnter() {

    tft->fillScreen(TFT_BLACK);
    needsRender = true;
}

void PauseScreen::onExit() {
    needsRender = true;
}

void PauseScreen::update() {

}

GameState PauseScreen::getState() {

    return GameState::PAUSE;
}

void PauseScreen::render() {

    tft->fillScreen(TFT_BLACK);

    tft->setTextColor(TFT_WHITE);

    tft->drawCentreString("PAUSADO", 160, 80, 4);

    tft->drawCentreString("SUPERIOR ESQUERDO = VOLTAR", 160, 150, 2);

    tft->drawCentreString("SUPERIOR DIREITO = RESETAR", 160, 180, 2);
}