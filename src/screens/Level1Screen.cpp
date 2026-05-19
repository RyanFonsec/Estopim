#include "Level1Screen.h"

#include "../math/MathGenerator.h"

Level1Screen::Level1Screen(
    TFT_eSPI* display,
    InputSystem* in
)

: hud(display)
{
    tft = display;

    input = in;

    lives = 3;

    score = 0;

    timeLeft = 15;

    levelState = LevelState::PLAYING;

    feedbackStart = 0;

    staticDrawn = false;
}

void Level1Screen::onEnter() {

    generateQuestion();

    needsRender = true;
}

void Level1Screen::onExit() {

}

GameState Level1Screen::getState() {

    return GameState::LEVEL1;
}

void Level1Screen::generateQuestion() {

    currentQuestion =
        MathGenerator::generateEasyQuestion();

    timeLeft = 15;

    levelState = LevelState::PLAYING;

    needsRender = true;

    staticDrawn = false;
}

void Level1Screen::checkAnswer(int answerIndex) {

    if(levelState != LevelState::PLAYING) {

        return;
    }

    if(answerIndex ==
       currentQuestion.correctIndex) {

        score += 100;

        levelState = LevelState::CORRECT;
    }
    else {

        lives--;

        levelState = LevelState::WRONG;
    }

    feedbackStart = millis();

    needsRender = true;
}

void Level1Screen::update() {

    // TIMER

    if(levelState == LevelState::PLAYING && timer.every(1000)) {

        timeLeft--;

        needsRender = true;

            if(timeLeft <= 0) {

            lives--;

            levelState = LevelState::TIMEOUT;

            feedbackStart = millis();

            needsRender = true;
        }
    }

    // INPUTS

    if(levelState == LevelState::PLAYING && input->wasPressed(Button::BTN_GREEN)){

        checkAnswer(0);
    }

    if(levelState == LevelState::PLAYING && input->wasPressed(Button::BTN_BLUE)){

        checkAnswer(1);
    }

    if(levelState == LevelState::PLAYING && input->wasPressed(Button::BTN_YELLOW)){

        checkAnswer(2);
    }

    // =====================================
    // FEEDBACK TIMER
    // =====================================

    if(levelState == LevelState::CORRECT ||
    levelState == LevelState::WRONG ||
    levelState == LevelState::TIMEOUT) {

        if(millis() - feedbackStart > 1200) {

            generateQuestion();
        }
    }
}

void Level1Screen::renderStatic() {

    tft->fillScreen(TFT_DARKGREY);

    // inimigo

    tft->fillRect(110, 50, 100, 50, TFT_RED);

    tft->drawCentreString("INIMIGO", 160, 65, 2);

    staticDrawn = true;
}

void Level1Screen::renderDynamic() {

    hud.render();

    // limpa área pergunta

    tft->fillRect(0, 110, 320, 130, TFT_DARKGREY);

    String question =

        String(currentQuestion.num1)
        + " "
        + currentQuestion.operation
        + " "
        + String(currentQuestion.num2)
        + " = ?";

    tft->drawCentreString(question, 160, 130, 4);

    // respostas...
}

void Level1Screen::render() {

    if(!staticDrawn) {

        renderStatic();
    }

    renderDynamic();
}