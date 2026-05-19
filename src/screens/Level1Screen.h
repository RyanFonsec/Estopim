#pragma once

#include <TFT_eSPI.h>

#include "BaseScreen.h"
#include "../math/Question.h"
#include "../game/HUD.h"
#include "../systems/InputSystem.h"
#include "../systems/TimerSystem.h"
#include "../game/LevelState.h"

class Level1Screen : public BaseScreen {

private:

    TFT_eSPI* tft;

    LevelState levelState;


    InputSystem* input;

    HUD hud;

    TimerSystem timer;

    Question currentQuestion;

    bool staticDrawn;

    int lives;

    int score;

    int timeLeft;

    unsigned long feedbackStart;

    void generateQuestion();

    void checkAnswer(int answerIndex);
    

public:

    Level1Screen(
        TFT_eSPI* display,
        InputSystem* in
        
    );

    void onEnter() override;

    void onExit() override;

    void update() override;

    void render() override;

    void renderStatic();

    void renderDynamic();

    GameState getState() override;

    
};