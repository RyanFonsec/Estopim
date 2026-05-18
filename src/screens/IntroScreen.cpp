#include "IntroScreen.h"

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

    tft->fillScreen(TFT_BLACK);

    // FUTURO:
    // Sprite da narrativa
    // tft->pushImage(...)

    tft->setTextColor(TFT_YELLOW);

    tft->drawCentreString("SALVADOR ESTA", 160, 20, 2);

    tft->drawCentreString("EM PERIGO!", 160, 45, 2);

    tft->setTextColor(TFT_WHITE);

    tft->drawString("Resolva desafios", 20, 90, 2);

    tft->drawString("matematicos para", 20, 115, 2);

    tft->drawString("salvar a cidade.", 20, 140, 2);

    tft->drawRect(40, 210, 240, 25, TFT_GREEN);

    tft->drawCentreString("VERDE = CONTINUAR", 160, 216, 2);
}