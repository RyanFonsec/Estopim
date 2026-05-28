#include "Level2Screen.h"

#include "../math/MathGenerator.h"

#include "../assets/backgrounds/level2_bg.h"
#include "../assets/sprites/enemy1.h"
#include "../assets/sprites/player_knife1.h"

// ======================================================
// BUFFER RESTORE BG
// ======================================================

static uint16_t bgLineBuffer[320];

// ======================================================
// RESTORE BACKGROUND
// ======================================================

static void restoreBg(
    TFT_eSPI* tft,
    const uint16_t* bg,
    int x,
    int y,
    int w,
    int h
) {

    // ==========================================
    // CLAMP TELA
    // ==========================================

    if(x < 0) {

        w += x;

        x = 0;
    }

    if(y < 0) {

        h += y;

        y = 0;
    }

    if(x + w > 320) {

        w = 320 - x;
    }

    if(y + h > 240) {

        h = 240 - y;
    }

    if(w <= 0 || h <= 0) {

        return;
    }

    // ==========================================
    // JANELA TFT
    // ==========================================

    tft->setAddrWindow(
        x,
        y,
        w,
        h
    );

    // ==========================================
    // RESTAURA LINHA A LINHA
    // ==========================================

    for(int row = 0; row < h; row++) {

        const uint16_t* src =

            bg
            + ((y + row) * 320)
            + x;

        memcpy_P(
            bgLineBuffer,
            src,
            w * sizeof(uint16_t)
        );

        tft->pushColors(
            bgLineBuffer,
            w,
            true
        );
    }
}

// ======================================================
// CONSTRUTOR
// ======================================================

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

// ======================================================
// ON ENTER
// ======================================================

void Level2Screen::onEnter() {

    feedback.begin();

    hud.setBackground(level2_bg);

    lives = 3;

    timeLeft = 15;

    finished = false;

    playerDead = false;

    staticDrawn = false;

    hudDirty = true;

    needsRender = true;

    lastEnemySpawn = 0;

    for(int i = 0; i < MAX_ENEMIES; i++) {

        enemies[i].active = false;
    }
}

// ======================================================
// GAME STATE
// ======================================================

GameState Level2Screen::getState() {

    return GameState::LEVEL2;
}

// ======================================================
// QUESTION
// ======================================================

Question Level2Screen::createQuestion() {

    return MathGenerator::generateSubtractionQuestion();
}

// ======================================================
// STATIC RENDER
// ======================================================

void Level2Screen::renderStatic() {

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

// ======================================================
// PLAYER
// ======================================================

void Level2Screen::renderPlayer() {

    tft->pushImage(
        10,
        96,
        32,
        32,
        player_knife1,
        TFT_BLACK
    );
}

// ======================================================
// CLEARS
// ======================================================

void Level2Screen::clearGameplayArea() {

    tft->pushImage(
        50,
        40,
        270,
        90,
        level2_bg + (40 * 320) + 50
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

// ======================================================
// SPAWN ENEMY
// ======================================================

void Level2Screen::spawnEnemy() {

    // ==========================================
    // LIMITE
    // ==========================================

    for(int i = 0; i < MAX_ENEMIES; i++) {

        if(enemies[i].active) {

            return;
        }
    }

    // ==========================================
    // SPAWN
    // ==========================================

    for(int i = 0; i < MAX_ENEMIES; i++) {

        if(!enemies[i].active) {

            Question q =

                MathGenerator::
                generateSubtractionQuestion();

            enemies[i].active = true;

            enemies[i].x = 280;

            enemies[i].y = 96;

            enemies[i].speed = 2;

            enemies[i].question = q;

            currentQuestion = q;

            questionDirty = true;

            needsRender = true;

            break;
        }
    }
}

// ======================================================
// STEP + DRAW
// ======================================================

static const int GHOST_X_PAD = 16;

static const int GHOST_Y_TOP = 22;

static const int SPRITE_W = 32;

static const int SPRITE_H = 32;

void Level2Screen::stepAndDrawEnemies() {

    tft->setSwapBytes(true);

    tft->setTextColor(
        TFT_WHITE,
        0x0000
    );

    for(int i = 0; i < MAX_ENEMIES; i++) {

        if(!enemies[i].active) {

            continue;
        }

        // ======================================
        // POSIÇÃO ANTIGA
        // ======================================

        int px = enemies[i].x;

        int py = enemies[i].y;

        // ======================================
        // LIMPA GHOST
        // ======================================

        restoreBg(
            tft,
            level2_bg,
            px - GHOST_X_PAD,
            py - GHOST_Y_TOP,
            SPRITE_W + (GHOST_X_PAD * 2),
            SPRITE_H + GHOST_Y_TOP
        );

        // ======================================
        // MOVE
        // ======================================

        enemies[i].x -= enemies[i].speed;

        // ======================================
        // PLAYER HIT
        // ======================================

        if(enemies[i].x <= 60) {

            restoreBg(
                tft,
                level2_bg,
                enemies[i].x - GHOST_X_PAD,
                py - GHOST_Y_TOP,
                SPRITE_W + (GHOST_X_PAD * 2),
                SPRITE_H + GHOST_Y_TOP
            );

            enemies[i].active = false;

            lives--;

            hudDirty = true;

            questionDirty = true;

            needsRender = true;

            feedback.error();

            continue;
        }

        // ======================================
        // NOVA POSIÇÃO
        // ======================================

        int nx = enemies[i].x;

        // ======================================
        // TEXTO
        // ======================================

        String operation =

            String(enemies[i].question.num1)
            + "-"
            + String(enemies[i].question.num2);

        tft->drawCentreString(
            operation,
            nx + 16,
            py - GHOST_Y_TOP + 4,
            2
        );

        // ======================================
        // SPRITE
        // ======================================

        tft->pushImage(
            nx,
            py,
            SPRITE_W,
            SPRITE_H,
            enemy1,
            TFT_BLACK
        );
    }
}

// ======================================================
// STUBS
// ======================================================

void Level2Screen::updateEnemies() {

}

void Level2Screen::renderEnemies() {

}

// ======================================================
// REMOVE ENEMY
// ======================================================

void Level2Screen::removeEnemy(int index) {

    int px = enemies[index].x;

    int py = enemies[index].y;

    restoreBg(
        tft,
        level2_bg,
        px - GHOST_X_PAD,
        py - GHOST_Y_TOP,
        SPRITE_W + (GHOST_X_PAD * 2),
        SPRITE_H + GHOST_Y_TOP
    );

    enemies[index].active = false;
}

// ======================================================
// CHECK ANSWER
// ======================================================

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

    // ==========================================
    // CORRETO
    // ==========================================

    if(answerIndex ==
       enemies[firstEnemy].question.correctIndex) {

        feedback.success();

        removeEnemy(firstEnemy);

        questionDirty = true;

        needsRender = true;
    }

    // ==========================================
    // ERRADO
    // ==========================================

    else {

        lives--;

        hudDirty = true;

        needsRender = true;

        feedback.error();
    }
}

void Level2Screen::checkAnswer(int index) {

    checkEnemyAnswer(index);
}

// ======================================================
// UPDATE
// ======================================================

void Level2Screen::update() {

    // ==========================================
    // TIMER
    // ==========================================

    if(timer.every(1000)) {

        timeLeft--;

        hudDirty = true;

        needsRender = true;
    }

    // ==========================================
    // SPAWN
    // ==========================================

    if(millis() - lastEnemySpawn >
       spawnInterval) {

        spawnEnemy();

        lastEnemySpawn = millis();
    }

    // ==========================================
    // MOVE + DRAW
    // ==========================================

    stepAndDrawEnemies();

    // ==========================================
    // INPUTS
    // ==========================================

    if(input->wasPressed(Button::BTN_GREEN)) {

        checkEnemyAnswer(0);
    }

    if(input->wasPressed(Button::BTN_BLUE)) {

        checkEnemyAnswer(1);
    }

    if(input->wasPressed(Button::BTN_YELLOW)) {

        checkEnemyAnswer(2);
    }

    // ==========================================
    // GAME OVER
    // ==========================================

    if(lives <= 0) {

        finished = true;

        playerDead = true;
    }

    // ==========================================
    // WIN
    // ==========================================

    if(timeLeft <= 0) {

        finished = true;
    }
}

// ======================================================
// RENDER
// ======================================================

void Level2Screen::render() {

    if(!needsRender) {

        return;
    }

    if(!staticDrawn) {

        renderStatic();

        staticDrawn = true;
    }

    renderHUD();

    renderQuestion();

    needsRender = false;
}

// ======================================================
// GAMEPLAY
// ======================================================

void Level2Screen::renderGameplay() {

    renderEnemies();
}

