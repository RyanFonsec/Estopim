#pragma once
#include "../systems/BgUtils.h"
#include "../core/BaseLevelScreen.h"

class Level3Screen : public BaseLevelScreen {

private:

    struct WallBlock {

        bool destroyed;

        Question question;
    };

    bool wallDirty;

    int destroyedBlocks;

    static const int TOTAL_BLOCKS = 6;

    WallBlock blocks[TOTAL_BLOCKS];
public:

    Level3Screen(
        TFT_eSPI* display,
        InputSystem* in,
        FeedbackSystem* feedback
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