#pragma once

#include <TFT_eSPI.h>

#include "../screens/BaseScreen.h"

#include "../math/Question.h"

#include "../game/HUD.h"

#include "../systems/InputSystem.h"
#include "../systems/TimerSystem.h"
#include "../systems/FeedbackSystem.h"

#include "../game/LevelState.h"

class BaseLevelScreen : public BaseScreen {

protected:

    TFT_eSPI* tft;

    InputSystem* input;

    HUD hud;

    TimerSystem timer;

    FeedbackSystem feedback;

    Question currentQuestion;

    LevelState levelState;

    bool staticDrawn;

    bool questionDirty;

    bool finished;

    bool playerDead;

    int lives;

    int score;

    int timeLeft;

    unsigned long feedbackStart;

public:

    BaseLevelScreen(
        TFT_eSPI* display,
        InputSystem* in
    );

    virtual void onEnter() override;

    virtual void onExit() override;

    virtual void update() override;

    virtual void render() override;

    bool isFinished();

    bool isPlayerDead();

protected:

    virtual Question createQuestion() = 0;

    virtual void renderStatic() = 0;

    virtual void clearQuestionArea() = 0;

    virtual void renderGameplay();

    void generateQuestion();

    void checkAnswer(int answerIndex);

    void renderHUD();

    void renderQuestion();
};