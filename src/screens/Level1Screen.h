#pragma once

#include "../core/BaseLevelScreen.h"

class Level1Screen : public BaseLevelScreen {

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
};