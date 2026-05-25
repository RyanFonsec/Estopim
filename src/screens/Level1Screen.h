// ============================================
// Level1Screen.h
// ============================================

#pragma once

#include <TFT_eSPI.h>

#include "BaseScreen.h"

#include "../math/Question.h"
#include "../game/HUD.h"
#include "../systems/InputSystem.h"
#include "../systems/TimerSystem.h"
#include "../systems/FeedbackSystem.h"
#include "../game/LevelState.h"

class Level1Screen : public BaseScreen {

private:

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

    // =========================
    // METHODS
    // =========================

    void generateQuestion();

    void checkAnswer(int answerIndex);

    void renderStatic();

    void renderDynamic();

    void renderQuestion();

public:

    Level1Screen(
        TFT_eSPI* display,
        InputSystem* in
    );

    void onEnter() override;

    void onExit() override;

    void update() override;

    void render() override;
    
    bool isFinished();

    bool isPlayerDead();

    GameState getState() override;
};