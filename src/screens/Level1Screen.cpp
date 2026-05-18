#include "Level1Screen.h"

Level1Screen::Level1Screen(TFT_eSPI* display) {

    tft = display;
}

void Level1Screen::onEnter() {

    tft->fillScreen(TFT_BLACK);
}

void Level1Screen::onExit() {

}

void Level1Screen::update() {

}

GameState Level1Screen::getState() {

    return GameState::LEVEL1;
}

void Level1Screen::render() {

    tft->fillScreen(TFT_DARKGREY);

    // =====================================
    // HUD
    // =====================================

    tft->setTextColor(TFT_WHITE);

    tft->drawString("VIDAS: 3", 10, 10, 2);

    tft->drawString("TEMPO: 15", 200, 10, 2);

    // =====================================
    // AREA DO JOGO
    // =====================================

    // FUTURO:
    // Sprite do inimigo
    // tft->pushImage(...)

    tft->fillRect(110, 50, 100, 60, TFT_RED);

    tft->drawCentreString("INIMIGO", 160, 70, 2);

    // =====================================
    // PERGUNTA
    // =====================================

    tft->setTextColor(TFT_YELLOW);

    tft->drawCentreString("7 + 5 = ?", 160, 140, 4);

    // =====================================
    // RESPOSTAS
    // =====================================

    // Verde
    tft->fillRect(15, 200, 80, 30, TFT_GREEN);

    tft->drawCentreString("12", 55, 208, 2);

    // Azul
    tft->fillRect(120, 200, 80, 30, TFT_BLUE);

    tft->drawCentreString("10", 160, 208, 2);

    // Amarelo
    tft->fillRect(225, 200, 80, 30, TFT_YELLOW);

    tft->setTextColor(TFT_BLACK);

    tft->drawCentreString("15", 265, 208, 2);
}