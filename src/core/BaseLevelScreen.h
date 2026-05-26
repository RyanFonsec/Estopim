#pragma once

#include <TFT_eSPI.h>

#include "../screens/BaseScreen.h"

#include "../math/Question.h"

#include "../game/HUD.h"
#include "../game/LevelState.h"

#include "../systems/InputSystem.h"
#include "../systems/TimerSystem.h"
#include "../systems/FeedbackSystem.h"

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

    bool hudDirty;

    bool questionDirty;

    bool finished;

    bool playerDead;

    int lives;

    int timeLeft;

    unsigned long feedbackStart;

public:

    BaseLevelScreen(
        TFT_eSPI* display,
        InputSystem* in
    );

    void onEnter() override;

    void onExit() override;

    void update() override;

    void render() override;

    bool isFinished();

    bool isPlayerDead();

protected:

    virtual Question createQuestion() = 0;

    virtual void renderStatic() = 0;

    virtual void renderGameplay() = 0;

    virtual void clearQuestionArea() = 0;

    virtual void clearTimerArea() = 0;

    void generateQuestion();

    void checkAnswer(int answerIndex);

    void renderHUD();

    void renderQuestion();
};