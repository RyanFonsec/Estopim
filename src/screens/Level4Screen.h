#pragma once
#include "../systems/BgUtils.h"
#include "../core/BaseLevelScreen.h"

struct ReverseEnemy {

    bool destroyed;

    Question question;

    int x;
    int y;

    bool leftSide;
};

class Level4Screen : public BaseLevelScreen {

private:

    static const int TOTAL_ENEMIES = 6;

    ReverseEnemy enemies[TOTAL_ENEMIES];

    int destroyedEnemies;

    bool wallDirty;

public:

    Level4Screen(
        TFT_eSPI* display,
        InputSystem* in,
        FeedbackSystem* feedback
    );

    GameState getState() override;

    void onEnter() override;
    void forceRedraw() override;
protected:

    Question createQuestion() override;

    void checkAnswer(int index) override;

    void renderStatic() override;

    void renderGameplay() override;

    void renderQuestion() override;

    void clearGameplayArea() override;

    void clearTimerArea() override;

    void clearQuestionArea() override;
};