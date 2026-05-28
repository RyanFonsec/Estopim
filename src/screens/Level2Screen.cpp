#include "Level2Screen.h"

#include "../math/MathGenerator.h"

#include "../assets/backgrounds/level2_bg.h"

#include "../assets/sprites/enemy1.h"

#include "../assets/sprites/player_cannon.h"

Level2Screen::Level2Screen(
    TFT_eSPI* display,
    InputSystem* input
)

: BaseLevelScreen(display, input)
{
    spawnInterval = 3000;

    lastEnemySpawn = 0;

    for(int i = 0; i < MAX_ENEMIES; i++) {

        enemies[i].active = false;
    }
}

void Level2Screen::onEnter() {

    BaseLevelScreen::onEnter();

    lives = 3;

    finished = false;

    playerDead = false;

    for(int i = 0; i < MAX_ENEMIES; i++) {

        enemies[i].active = false;
    }
}

GameState Level2Screen::getState() {

    return GameState::LEVEL2;
}

Question Level2Screen::createQuestion() {

    return MathGenerator::generateSubtractionQuestion();
}

void Level2Screen::renderStatic(){

    tft->setSwapBytes(true);

    tft->pushImage(
        0,
        0,
        320,
        240,
        level2_bg
    );

    renderPlayer();
}

void Level2Screen::renderPlayer() {

    tft->pushImage(
        10,
        80,
        64,
        64,
        player_cannon,
        TFT_BLACK
    );
}

void Level2Screen::clearGameplayArea() {

    tft->pushImage(
        80,
        40,
        240,
        100,
        level2_bg + (40 * 320) + 80
    );
}

void Level2Screen::clearTimerArea() {

    tft->pushImage(
        0,
        130,
        320,
        30,
        level2_bg + (130 * 320)
    );
}

void Level2Screen::clearQuestionArea() {

    tft->pushImage(
        0,
        160,
        320,
        80,
        level2_bg + (160 * 320)
    );
}

void Level2Screen::spawnEnemy() {

    for(int i = 0; i < MAX_ENEMIES; i++) {

        if(!enemies[i].active) {

            enemies[i].active = true;

            enemies[i].x = 280;

            enemies[i].y = 70;

            enemies[i].speed = 2;

            enemies[i].question =
                MathGenerator::generateSubtractionQuestion();

            break;
        }
    }
}

void Level2Screen::updateEnemies() {

    for(int i = 0; i < MAX_ENEMIES; i++) {

        if(!enemies[i].active) {

            continue;
        }

        enemies[i].x -= enemies[i].speed;

        if(enemies[i].x <= 60) {

            enemies[i].active = false;

            lives--;

            hudDirty = true;

            feedback.error();
        }
    }
}

void Level2Screen::renderEnemies() {

    for(int i = 0; i < MAX_ENEMIES; i++) {

        if(!enemies[i].active) {

            continue;
        }

        tft->pushImage(
            enemies[i].x,
            enemies[i].y,
            32,
            32,
            enemy1,
            TFT_BLACK
        );

        tft->setTextColor(TFT_WHITE);

        String operation =

            String(enemies[i].question.num1)
            + "-"
            + String(enemies[i].question.num2);

        tft->drawCentreString(
            operation,
            enemies[i].x + 16,
            enemies[i].y - 20,
            2
        );
    }
}

void Level2Screen::removeEnemy(int index) {

    enemies[index].active = false;
}

void Level2Screen::checkEnemyAnswer(int answerIndex) {

    int firstEnemy = -1;

    for(int i = 0; i < MAX_ENEMIES; i++) {

        if(enemies[i].active) {

            firstEnemy = i;

            break;
        }
    }

    if(firstEnemy == -1) {

        return;
    }

    if(answerIndex ==
       enemies[firstEnemy].question.correctIndex) {

        feedback.success();

        removeEnemy(firstEnemy);
    }
    else {

        lives--;

        feedback.error();
    }

    hudDirty = true;

    needsRender = true;
}

void Level2Screen::update() {

    BaseLevelScreen::update();

    if(millis() - lastEnemySpawn > spawnInterval) {

        spawnEnemy();

        lastEnemySpawn = millis();

        needsRender = true;
    }

    updateEnemies();

    needsRender = true;
}

void Level2Screen::renderGameplay() {

    clearGameplayArea();

    renderPlayer();

    renderEnemies();
}

void Level2Screen::checkAnswer(int index) {

    checkEnemyAnswer(index);
}