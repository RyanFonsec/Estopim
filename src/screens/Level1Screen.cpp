#include "Level1Screen.h"

#include "../math/MathGenerator.h"
#include "../assets/backgrounds/level1_bg.h"
#include "../assets/sprites/player_cannon.h"

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

    questionDirty = true;

    feedbackDirty = true;
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

    questionDirty = true;

    feedbackDirty = true;

    needsRender = true;
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

    feedbackDirty = true;
    
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

    tft->setSwapBytes(true);

    // HUD background

    tft->fillRect(0, 0, 320, 30, TFT_BLACK);

    // Área gameplay
    tft->pushImage(
        0,
        0,
        320,
        240,
        level1_bg
    );

    // Personagem do jogador
    tft->pushImage(
        128,
        50,
        64,
        64,
        player_cannon,
        TFT_BLACK
    );

    staticDrawn = true;
}

void Level1Screen::renderDynamic() {

    // =========================
    // UPDATE HUD DATA
    // =========================

    hud.setLives(lives);

    hud.setScore(score);

    hud.setTime(timeLeft);

    // =========================
    // RENDER HUD
    // =========================

    hud.render();

    // =========================
    // RENDER GAMEPLAY
    // =========================

    renderQuestion();

    renderFeedback();
}

void Level1Screen::renderQuestion() {

    if(!questionDirty) {

        return;
    }

    // limpa área pergunta

    tft->pushImage(
    0,
    110,
    320,
    120,
    level1_bg + (110 * 320)
    );

    tft->setTextColor(TFT_WHITE);

    String question =

        String(currentQuestion.num1)
        + " "
        + currentQuestion.operation
        + " "
        + String(currentQuestion.num2)
        + " = ?";

    tft->drawCentreString(
        question,
        160,
        130,
        4
    );

    // =========================
    // BOTÃO VERDE
    // =========================

    tft->fillRect(
        10,
        200,
        90,
        30,
        TFT_GREEN
    );

    tft->drawCentreString(
        String(currentQuestion.options[0]),
        55,
        208,
        2
    );

    // =========================
    // BOTÃO AZUL
    // =========================

    tft->fillRect(
        115,
        200,
        90,
        30,
        TFT_BLUE
    );

    tft->drawCentreString(
        String(currentQuestion.options[1]),
        160,
        208,
        2
    );

    // =========================
    // BOTÃO AMARELO
    // =========================

    tft->fillRect(
        220,
        200,
        90,
        30,
        TFT_YELLOW
    );

    tft->setTextColor(TFT_BLACK);

    tft->drawCentreString(
        String(currentQuestion.options[2]),
        265,
        208,
        2
    );

    questionDirty = false;
}

void Level1Screen::renderFeedback() {

    if(!feedbackDirty) {

        return;
    }

    // limpa área feedback

    tft->pushImage(
        0,
        160,
        320,
        30,
        level1_bg + (160 * 320)
    );

    switch(levelState) {

        case LevelState::CORRECT:

            tft->setTextColor(TFT_GREEN);

            tft->drawCentreString(
                "CORRETO!",
                160,
                165,
                2
            );

            break;

        case LevelState::WRONG:

            tft->setTextColor(TFT_RED);

            tft->drawCentreString(
                "ERRADO!",
                160,
                165,
                2
            );

            break;

        case LevelState::TIMEOUT:

            tft->setTextColor(TFT_ORANGE);

            tft->drawCentreString(
                "TEMPO ESGOTADO!",
                160,
                165,
                2
            );

            break;

        default:
            break;
    }

    feedbackDirty = false;
}

void Level1Screen::render() {

    if(!staticDrawn) {

        renderStatic();
    }

    renderDynamic();
}