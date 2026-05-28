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
    correctAnswers = 0;
}

void Level1Screen::onEnter() {

    BaseLevelScreen::onEnter();

    hud.setBackground(level1_bg);
    
    correctAnswers = 0;
}

GameState Level1Screen::getState() {

    return GameState::LEVEL1;
}

Question Level1Screen::createQuestion() {

    return MathGenerator::generateEasyQuestion();
}

void Level1Screen::checkAnswer(int index) {

    // reutiliza lógica original
    BaseLevelScreen::checkAnswer(index);

    // se acertou
    if(lastAnswerCorrect) {

        correctAnswers++;

        if(correctAnswers >= 5) {

            finished = true;
        }
    }
}

void Level1Screen::renderStatic() {

    tft->fillScreen(TFT_BLACK);

    tft->setSwapBytes(true);

    tft->pushImage(
        0,
        0,
        320,
        240,
        level1_bg
    );

    tft->pushImage(
        15,
        70,
        64,
        64,
        player_cannon,
        TFT_BLACK
    );
}

void Level1Screen::clearTimerArea() {

    tft->pushImage(
        0,
        135,
        320,
        20,
        level1_bg + (135 * 320)
    );
}

void Level1Screen::clearQuestionArea() {

    tft->pushImage(
        0,
        140,
        320,
        100,
        level1_bg + (140 * 320)
    );
}

void Level1Screen::clearGameplayArea() {

    tft->pushImage(
        90,
        40,
        0,
        0,
        level1_bg + (40 * 320) + 90
    );
}


void Level1Screen::renderGameplay() {

    clearGameplayArea();
}

