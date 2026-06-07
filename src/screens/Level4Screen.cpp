#include "Level4Screen.h"

#include "../math/MathGenerator.h"

#include "../assets/backgrounds/level4_bg.h"

#include "../assets/sprites/enemy_left.h"
#include "../assets/sprites/enemy_right.h"

Level4Screen::Level4Screen(
    TFT_eSPI* display,
    InputSystem* in,
    FeedbackSystem* feedback
)

: BaseLevelScreen(display, in, feedback)
{
    destroyedEnemies = 0;

    wallDirty = true;
}

GameState Level4Screen::getState() {

    return GameState::LEVEL4;
}

void Level4Screen::onEnter() {

    BaseLevelScreen::onEnter();

    hud.setBackground(level4_bg);

    destroyedEnemies = 0;

    wallDirty = true;

    int positions[6][2] = {

        {20, 100},
        {60, 100},
        {100, 100},

        {220, 100},
        {260, 100},
        {300, 100}
    };

    for(int i = 0; i < TOTAL_ENEMIES; i++) {

        enemies[i].destroyed = false;

        enemies[i].question =
            MathGenerator::generateReverseQuestion();

        enemies[i].x =
            positions[i][0];

        enemies[i].y =
            positions[i][1];

        enemies[i].leftSide =
            (i < 3);
    }

    currentQuestion =
        enemies[0].question;

    questionDirty = true;

    hudDirty = true;

    needsRender = true;
}

Question Level4Screen::createQuestion() {

    return MathGenerator::generateReverseQuestion();
}

void Level4Screen::checkAnswer(int index) {

    if(index == currentQuestion.correctIndex) {

        feedback->success();

        enemies[destroyedEnemies]
            .destroyed = true;

        destroyedEnemies++;

        timeLeft = 15;

        hudDirty = true;

        wallDirty = true;

        if(destroyedEnemies >= TOTAL_ENEMIES) {

            finished = true;
        }
        else {

            currentQuestion =
                enemies[destroyedEnemies]
                .question;

            questionDirty = true;
        }

        needsRender = true;
    }
    else {

        feedback->error();

        lives--;

        hudDirty = true;

        needsRender = true;

        if(lives <= 0) {

            finished = true;

            playerDead = true;
        }
    }
}

void Level4Screen::renderStatic() {

    tft->setSwapBytes(true);

    tft->pushImage(
        0,
        0,
        320,
        240,
        (uint16_t*)level4_bg
    );
}

void Level4Screen::clearGameplayArea() {

    BgUtils::restore(
        tft,
        level4_bg,
        0,
        40,
        320,
        100
    );
}

void Level4Screen::clearTimerArea() {

    BgUtils::restore(
        tft,
        level4_bg,
        0,
        140,
        320,
        30
    );
}

void Level4Screen::clearQuestionArea() {

    BgUtils::restore(
        tft,
        level4_bg,
        0,
        160,
        320,
        80
    );
}

void Level4Screen::renderQuestion() {

    if(!questionDirty) {

        return;
    }

    clearQuestionArea();

    tft->setTextColor(TFT_WHITE);

    String question;

    switch(currentQuestion.operation) {

        case '+':
            question =
                "? + " +
                String(currentQuestion.num2) +
                " = " +
                String(currentQuestion.num1);
            break;

        case '-':
            question =
                String(currentQuestion.num1) +
                " - ? = " +
                String(currentQuestion.num2);
            break;

        case '*':
            question =
                "? x " +
                String(currentQuestion.num2) +
                " = " +
                String(currentQuestion.num1);
            break;

        case '/':
            question =
                String(currentQuestion.num1) +
                " / ? = " +
                String(currentQuestion.num2);
            break;
    }

    tft->drawString(
        "CALCULE " + question,
        10,
        165,
        2
    );

    // Verde
    tft->fillRect(
        10,
        195,
        90,
        30,
        TFT_GREEN
    );

    tft->setTextColor(TFT_WHITE);

    tft->drawCentreString(
        String(currentQuestion.options[0]),
        55,
        203,
        2
    );

    // VERMELHO
    tft->fillRect(
        115,
        195,
        90,
        30,
        TFT_RED
    );

    tft->drawCentreString(
        String(currentQuestion.options[1]),
        160,
        203,
        2
    );

    // azuL
    tft->fillRect(
        220,
        195,
        90,
        30,
        TFT_BLUE
    );

    tft->setTextColor(TFT_WHITE);

    tft->drawCentreString(
        String(currentQuestion.options[2]),
        265,
        203,
        2
    );

    questionDirty = false;
}

void Level4Screen::renderGameplay() {

    if(!wallDirty) {

        return;
    }

    clearGameplayArea();

    tft->setSwapBytes(true);

    for(int i = destroyedEnemies;
        i < TOTAL_ENEMIES;
        i++)
    {
        if(enemies[i].leftSide) {

            tft->pushImage(
                enemies[i].x,
                enemies[i].y,
                32,
                32,
                (uint16_t*)enemy_left,
                TFT_GREEN
            );
        }
        else {

            tft->pushImage(
                enemies[i].x,
                enemies[i].y,
                32,
                32,
                (uint16_t*)enemy_right,
                TFT_GREEN
            );
        }
    }

    wallDirty = false;
}