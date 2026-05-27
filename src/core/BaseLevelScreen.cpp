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

    timeLeft = 15;

    staticDrawn = false;

    hudDirty = true;

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

    hudDirty = true;
}

void BaseLevelScreen::checkAnswer(int answerIndex) {

    if(levelState != LevelState::PLAYING) {

        return;
    }

    if(answerIndex ==
       currentQuestion.correctIndex) {

        levelState = LevelState::CORRECT;

        feedback.success();
    }
    else {

        lives--;

        levelState = LevelState::WRONG;

        feedback.error();

        hudDirty = true;
    }

    feedbackStart = millis();
}

void BaseLevelScreen::update() {

    // =====================================
    // TIMER
    // =====================================

    if(levelState == LevelState::PLAYING &&
       timer.every(1000)) {

        timeLeft--;

        hudDirty = true;

        needsRender = true;

        if(timeLeft <= 0) {

            lives--;

            hudDirty = true;

            levelState = LevelState::TIMEOUT;

            feedback.timeout();

            feedbackStart = millis();

            needsRender = true;
        }
    }

    // =====================================
    // INPUTS
    // =====================================

    if(levelState == LevelState::PLAYING) {

        if(input->wasPressed(Button::BTN_GREEN)) {

            checkAnswer(0);
        }

        if(input->wasPressed(Button::BTN_BLUE)) {

            checkAnswer(1);
        }

        if(input->wasPressed(Button::BTN_YELLOW)) {

            checkAnswer(2);
        }
    }

    // =====================================
    // FEEDBACK TIMER
    // =====================================

    if(levelState != LevelState::PLAYING) {

        if(millis() - feedbackStart > 1200) {

            generateQuestion();

            questionDirty = true;

            hudDirty = true;

            needsRender = true;
        }
    }

    // =====================================
    // GAME OVER
    // =====================================

    if(lives <= 0) {

        finished = true;

        playerDead = true;
    }
}

void BaseLevelScreen::render() {

    if(!needsRender) {

        return;
    }

    if(!staticDrawn) {

        renderStatic();

        staticDrawn = true;
    }

    renderHUD();

    renderQuestion();

    renderGameplay();
    
    needsRender = false;
}

void BaseLevelScreen::renderHUD() {

    if(!hudDirty) {

        return;
    }

    clearTimerArea();

    hud.setLives(lives);

    hud.setTime(timeLeft);

    hud.render();

    hudDirty = false;
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

    tft->drawString(
        "CALCULE " + question,
        10,
        165,
        2
    );

    // VERDE

    tft->fillRect(
        10,
        195,
        90,
        30,
        TFT_GREEN
    );

    tft->drawCentreString(
        String(currentQuestion.options[0]),
        55,
        203,
        2
    );

    // AZUL

    tft->fillRect(
        115,
        195,
        90,
        30,
        TFT_BLUE
    );

    tft->setTextColor(TFT_WHITE);

    tft->drawCentreString(
        String(currentQuestion.options[1]),
        160,
        203,
        2
    );

    // AMARELO

    tft->fillRect(
        220,
        195,
        90,
        30,
        TFT_YELLOW
    );

    tft->setTextColor(TFT_BLACK);

    tft->drawCentreString(
        String(currentQuestion.options[2]),
        265,
        203,
        2
    );

    questionDirty = false;
}

bool BaseLevelScreen::isFinished() {

    return finished;
}

bool BaseLevelScreen::isPlayerDead() {

    return playerDead;
}