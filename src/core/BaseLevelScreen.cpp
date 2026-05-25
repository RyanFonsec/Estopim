#include "BaseLevelScreen.h"

BaseLevelScreen::BaseLevelScreen(
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

    staticDrawn = false;

    questionDirty = true;

    finished = false;

    playerDead = false;
}

void BaseLevelScreen::onEnter() {

    feedback.begin();

    generateQuestion();

    needsRender = true;
}

void BaseLevelScreen::onExit() {

}

void BaseLevelScreen::generateQuestion() {

    feedback.clear();

    currentQuestion = createQuestion();

    timeLeft = 15;

    levelState = LevelState::PLAYING;

    questionDirty = true;

    needsRender = true;
}

void BaseLevelScreen::checkAnswer(int answerIndex) {

    if(levelState != LevelState::PLAYING) {

        return;
    }

    if(answerIndex ==
       currentQuestion.correctIndex) {

        score += 100;

        feedback.success();
    }
    else {

        lives--;

        feedback.error();
    }

    feedbackStart = millis();

    levelState = LevelState::CORRECT;

    if(answerIndex != currentQuestion.correctIndex) {

        levelState = LevelState::WRONG;
    }
}

void BaseLevelScreen::update() {

    // TIMER

    if(levelState == LevelState::PLAYING &&
    timer.every(1000)) {

        timeLeft--;

        hud.setTime(timeLeft);

        needsRender = true;

        if(timeLeft <= 0) {

            lives--;

            hud.setLives(lives);

            levelState = LevelState::TIMEOUT;

            feedback.timeout();

            feedbackStart = millis();

            needsRender = true;
        }
    }

    // INPUTS

    if(levelState == LevelState::PLAYING && input->wasPressed(Button::BTN_GREEN)) {

        checkAnswer(0);
    }

    if(levelState == LevelState::PLAYING &&
       input->wasPressed(Button::BTN_BLUE)) {

        checkAnswer(1);
    }

    if(levelState == LevelState::PLAYING &&
       input->wasPressed(Button::BTN_YELLOW)) {

        checkAnswer(2);
    }

    // FEEDBACK TIMER

    if(levelState != LevelState::PLAYING) {

        if(millis() - feedbackStart > 1200) {

            generateQuestion();
        }
    }

    // GAME OVER

    if(lives <= 0) {

        finished = true;

        playerDead = true;
    }
}

void BaseLevelScreen::render() {

    if(!staticDrawn) {

        renderStatic();

        staticDrawn = true;
    }

    renderHUD();

    renderQuestion();

    renderGameplay();
}

void BaseLevelScreen::renderHUD() {

    hud.setLives(lives);

    hud.setTime(timeLeft);

    hud.render();
}

void BaseLevelScreen::renderQuestion() {

    if(!questionDirty) {

        return;
    }

    clearQuestionArea();

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
        150,
        4
    );

    // VERDE

    tft->fillRect(
        10,
        200,
        90,
        30,
        TFT_GREEN
    );

    tft->setTextColor(TFT_BLACK);

    tft->drawCentreString(
        String(currentQuestion.options[0]),
        55,
        208,
        2
    );

    // AZUL

    tft->fillRect(
        115,
        200,
        90,
        30,
        TFT_BLUE
    );

    tft->setTextColor(TFT_WHITE);

    tft->drawCentreString(
        String(currentQuestion.options[1]),
        160,
        208,
        2
    );

    // AMARELO

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

void BaseLevelScreen::renderGameplay() {

}

bool BaseLevelScreen::isFinished() {

    return finished;
}

bool BaseLevelScreen::isPlayerDead() {

    return playerDead;
}