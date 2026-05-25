#include "GameOverScreen.h"

GameOverScreen::GameOverScreen(TFT_eSPI* display) {
    tft = display;
}

void GameOverScreen::onEnter() {

    tft->fillScreen(TFT_BLACK);
}

void GameOverScreen::onExit() {

}


void GameOverScreen::update() {

}

GameState GameOverScreen::getState() {

    return GameState::GAME_OVER;
}

void GameOverScreen::render() {

    tft->fillScreen(TFT_RED);

    // FUTURO:
    // Sprite derrota

    tft->setTextColor(TFT_WHITE);

    tft->drawCentreString("GAME OVER", 160, 100, 4);

    tft->drawCentreString("A CIDADE CAIU...", 160, 150, 2);
}