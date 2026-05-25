#include "Level1Screen.h"

#include "../math/MathGenerator.h"

#include "../assets/backgrounds/level1_bg.h"

#include "../assets/sprites/player_cannon.h"

Level1Screen::Level1Screen(
    TFT_eSPI* display,
    InputSystem* in
)

: BaseLevelScreen(display, in)
{

}

GameState Level1Screen::getState() {

    return GameState::LEVEL1;
}

Question Level1Screen::createQuestion() {

    return MathGenerator::generateEasyQuestion();
}

void Level1Screen::clearQuestionArea() {

    tft->pushImage(
        0,
        130,
        320,
        120,
        level1_bg + (130 * 320)
    );
}

void Level1Screen::renderStatic() {

    tft->fillScreen(TFT_BLACK);

    tft->setSwapBytes(true);

    // BACKGROUND

    tft->pushImage(
        0,
        0,
        320,
        240,
        level1_bg
    );

    // PLAYER

    tft->pushImage(
        15,
        80,
        64,
        64,
        player_cannon,
        TFT_BLACK
    );
}