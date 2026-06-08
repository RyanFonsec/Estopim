#include "BaseLevelScreen.h"

BaseLevelScreen::BaseLevelScreen(
    TFT_eSPI* display,
    InputSystem* in,
    FeedbackSystem* fb
)

: hud(display)
{

    feedback = fb;

    tft = display;

    input = in;

    lives = 3;

    timeLeft = 15;

    staticDrawn = false;

    hudDirty = true;

    questionDirty = true;

    finished = false;

    playerDead = false;

    needsRender = true;
}

void BaseLevelScreen::onEnter() {

    feedback->begin();

    generateQuestion();

    staticDrawn = false;

    needsRender = true;
}

void BaseLevelScreen::onExit() {
    feedback->clear();
}

void BaseLevelScreen::generateQuestion() {

    feedback->clear();

    currentQuestion = createQuestion();

    timeLeft = 15;

    levelState = LevelState::PLAYING;

    questionDirty = true;

    hudDirty = true;

    needsRender = true;
}

void BaseLevelScreen::checkAnswer(int answerIndex) {

    if(levelState != LevelState::PLAYING) {

        return;
    }

    if(answerIndex ==
       currentQuestion.correctIndex) {

        levelState = LevelState::CORRECT;

        feedback->success();

        lastAnswerCorrect = true;
    }
    else {

        lives--;

        levelState = LevelState::WRONG;

        feedback->error();

        hudDirty = true;

        lastAnswerCorrect = false;
    }

    feedbackStart = millis();

    needsRender = true;
}

void BaseLevelScreen::update() {

    feedback->update();
    
    if(levelState == LevelState::PLAYING &&
       timer.every(1000)) {

        timeLeft--;

        hudDirty = true;

        needsRender = true;

        if(timeLeft <= 0) {

            lives--;

            hudDirty = true;

            levelState = LevelState::TIMEOUT;

            feedback->timeout();

            feedbackStart = millis();

            needsRender = true;
        }
    }

    if(levelState == LevelState::PLAYING) {

        if(input->wasPressed(Button::BTN_GREEN)) {

            checkAnswer(0);
        }

        if(input->wasPressed(Button::BTN_RED)) {

            checkAnswer(1);
        }

        if(input->wasPressed(Button::BTN_BLUE)) {

            checkAnswer(2);
        }
    }

    if(levelState != LevelState::PLAYING) {

        if(millis() - feedbackStart > 1200) {

            generateQuestion();
        }
    }

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

    // =====================================
    // SÓ DESENHA QUESTÃO SE HABILITADO
    // =====================================

    if(showQuestionUI) {

        renderQuestion();
    }

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

    tft->setTextColor(TFT_BLACK);

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

    tft->fillRect(
        35,
        190,
        40,
        40,
        TFT_GREEN
    );

    tft->drawCentreString(
        String(currentQuestion.options[0]),
        55,
        203,
        2
    );

    tft->fillRect(
        140,
        190,
        40,
        40,
        TFT_RED
    );

    tft->setTextColor(TFT_WHITE);

    tft->drawCentreString(
        String(currentQuestion.options[1]),
        160,
        203,
        2
    );

    tft->fillRect(
        245,
        190,
        40,
        40,
        TFT_BLUE
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