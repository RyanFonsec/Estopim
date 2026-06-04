#include "Level3Screen.h"

#include "../math/MathGenerator.h"
#include "../assets/backgrounds/level3_bg.h"

Level3Screen::Level3Screen(
    TFT_eSPI* display,
    InputSystem* in
)

: BaseLevelScreen(display, in)
{
    destroyedBlocks = 0;
}

void Level3Screen::onEnter() {

    BaseLevelScreen::onEnter();

    hud.setBackground(level3_bg);

    destroyedBlocks = 0;

    wallDirty = true;

    for(int i = 0; i < TOTAL_BLOCKS; i++) {

        blocks[i].destroyed = false;

        blocks[i].question =
            MathGenerator::generateWallQuestion();
    }

    currentQuestion =
        blocks[0].question;

    questionDirty = true;
    hudDirty = true;
    needsRender = true;
}

GameState Level3Screen::getState() {

    return GameState::LEVEL3;
}

Question Level3Screen::createQuestion() {

    return MathGenerator::generateWallQuestion();
}

void Level3Screen::checkAnswer(int index) {

    if(index == currentQuestion.correctIndex)
    {
        feedback.success();

        blocks[destroyedBlocks].destroyed = true;

        destroyedBlocks++;
        wallDirty = true;
        timeLeft = 15;
        hudDirty = true;

        if(destroyedBlocks >= TOTAL_BLOCKS) {

            finished = true;
        }
        else {

            currentQuestion =
                blocks[destroyedBlocks]
                .question;

            questionDirty = true;
        }

        needsRender = true;
    }
    else {

        feedback.error();

        lives--;

        hudDirty = true;
        needsRender = true;

        if(lives <= 0) {

            finished = true;
            playerDead = true;
        }
    }
}

void Level3Screen::renderStatic() {

    tft->setSwapBytes(true);

    tft->pushImage(
        0,
        0,
        320,
        240,
        (uint16_t*)level3_bg
    );
}

void Level3Screen::clearGameplayArea() {

    BgUtils::restore(
        tft,
        level3_bg,
        50,
        40,
        220,
        90
    );
}

void Level3Screen::clearTimerArea() {

    BgUtils::restore(
        tft,
        level3_bg,
        0,
        130,
        320,
        30
    );
}

void Level3Screen::clearQuestionArea() {

    BgUtils::restore(
        tft,
        level3_bg,
        0,
        160,
        320,
        80
    );
}

void Level3Screen::renderGameplay() {

    if(!wallDirty) {
        return;
    }

    clearGameplayArea();

    int remaining =
        TOTAL_BLOCKS - destroyedBlocks;

    int startX = 90;
    int startY = 40;

    int w = 40;
    int h = 30;

    for(int i = 0; i < remaining; i++) {

        int blockIndex =
            destroyedBlocks + i;

        int col = i % 3;
        int row = i / 3;

        int x =
            startX + (col * 45);

        int y =
            startY + (row * 35);

        Question& q =
            blocks[blockIndex]
            .question;

        String expr =
            String(q.num1) +
            q.operation +
            String(q.num2);

        tft->fillRect(
            x,
            y,
            w,
            h,
            TFT_DARKGREY
        );

        tft->drawRect(
            x,
            y,
            w,
            h,
            TFT_WHITE
        );

        tft->setTextColor(
            TFT_WHITE,
            TFT_DARKGREY
        );

        tft->drawCentreString(
            expr,
            x + (w / 2),
            y + 8,
            2
        );
    }

    wallDirty = false;
}