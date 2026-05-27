#include "Level2Screen.h"

#include "../math/MathGenerator.h"

//#include "../assets/backgrounds/level2_bg.h"

//#include "../assets/sprites/enemy1.h"

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

    staticDrawn = false;

    finished = false;

    playerDead = false;

    lives = 3;

    hudDirty = true;

    feedback.begin();
}


GameState Level2Screen::getState() {

    return GameState::LEVEL2;
}

Question Level2Screen::createQuestion() {

    return MathGenerator::generateSubtractionQuestion();
}

void Level2Screen::renderStatic(){

    tft->setSwapBytes(true);
/*
    tft->pushImage(
        0,
        0,
        320,
        240,
        level2_bg
    );
*/

tft->fillScreen(TFT_DARKGREY);

    // ============================================
    // PLAYER
    // ============================================

    tft->pushImage(
        10,
        80,
        64,
        64,
        player_cannon,
        TFT_BLACK
    );
}

/*void Level2Screen::clearGameplayArea() {

    tft->pushImage(
        0,
        40,
        320,
        100,
        level2_bg + (40 * 320)
    );
}
*/

void Level2Screen::spawnEnemy() {

    for(int i = 0; i < MAX_ENEMIES; i++) {

        if(!enemies[i].active) {

            enemies[i].active = true;

            enemies[i].x = -40;

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

        enemies[i].x += enemies[i].speed;

        // ============================================
        // PLAYER HIT
        // ============================================

        if(enemies[i].x >= 220) {

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

        /*tft->pushImage(
            enemies[i].x,
            enemies[i].y,
            32,
            32,
            enemy1,
            TFT_BLACK
        );*/
        tft->fillRect(
    enemies[i].x,
    enemies[i].y,
    32,
    32,
    TFT_RED
);
    }
}

void Level2Screen::renderOperations() {

    tft->setTextColor(TFT_WHITE);

    for(int i = 0; i < MAX_ENEMIES; i++) {

        if(!enemies[i].active) {

            continue;
        }

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

    for(int i = index; i < MAX_ENEMIES - 1; i++) {

        enemies[i] = enemies[i + 1];
    }

    enemies[MAX_ENEMIES - 1].active = false;
}

void Level2Screen::checkEnemyAnswer(int answerIndex) {

    // ============================================
    // PROCURA PRIMEIRO INIMIGO
    // ============================================

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

        hudDirty = true;
    }
    else {

        lives--;

        hudDirty = true;

        feedback.error();
    }
}

void Level2Screen::update() {

    BaseLevelScreen::update();
    
    // ============================================
    // TIMER DA FASE
    // ============================================

    if(timer.every(1000)) {

        timeLeft--;

        hudDirty = true;
    }

    // ============================================
    // SPAWN DOS INIMIGOS
    // ============================================

    if(millis() - lastEnemySpawn > spawnInterval) {

        spawnEnemy();

        lastEnemySpawn = millis();
    }

    // ============================================
    // MOVIMENTAÇÃO
    // ============================================

    updateEnemies();

    // ============================================
    // INPUTS
    // ============================================

    if(input->wasPressed(Button::BTN_GREEN)) {

        checkEnemyAnswer(0);
    }

    if(input->wasPressed(Button::BTN_BLUE)) {

        checkEnemyAnswer(1);
    }

    if(input->wasPressed(Button::BTN_YELLOW)) {

        checkEnemyAnswer(2);
    }

    // ============================================
    // GAME OVER
    // ============================================

    if(lives <= 0) {

        finished = true;

        playerDead = true;
    }

    // ============================================
    // FASE COMPLETA
    // ============================================

    if(timeLeft <= 0) {

        finished = true;
    }
}

void Level2Screen::renderGameplay() {

    clearGameplayArea();

    renderEnemies();

    renderOperations();
}

void Level2Screen::clearGameplayArea() {

    tft->fillRect(
        0,
        40,
        320,
        100,
        TFT_DARKGREY
    );
}

void Level2Screen::clearTimerArea() {

    tft->fillRect(
        0,
        140,
        320,
        20,
        TFT_DARKGREY
    );
}

void Level2Screen::clearQuestionArea() {

    tft->fillRect(
        0,
        160,
        320,
        80,
        TFT_DARKGREY
    );
}