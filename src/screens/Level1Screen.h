#pragma once

#include "../core/BaseLevelScreen.h"

class Level1Screen : public BaseLevelScreen {

private:

    int correctAnswers;

public:

    Level1Screen(
        TFT_eSPI* display,
        InputSystem* in
    );

    GameState getState() override;

protected:

    Question createQuestion() override;

    void renderStatic() override;

    void clearQuestionArea() override;

    void clearGameplayArea() override;

    void clearTimerArea() override;

    void renderGameplay() override;

    void checkAnswer(int index) override;

    void onEnter() override;
};