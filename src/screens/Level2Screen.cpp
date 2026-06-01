#include "Level2Screen.h"
#include "../math/MathGenerator.h"
#include "../assets/backgrounds/level2_bg.h"
#include "../assets/sprites/enemy1.h"
#include "../assets/sprites/player_knife1.h"

Level2Screen::Level2Screen(TFT_eSPI* display, InputSystem* input)
    : BaseLevelScreen(display, input),
      enemySprite(display)
{
    spawnInterval  = 3000;
    lastEnemySpawn = 0;
    lastMove       = 0;

    for (int i = 0; i < MAX_ENEMIES; i++)
        enemies[i].active = false;

    // SPR_W + MAX_SPEED garante espaço para o drift
    // sem recriar o sprite a cada frame
    enemySprite.createSprite(SPR_W + MAX_SPEED, SPR_H);
    enemySprite.setSwapBytes(true);
}

Level2Screen::~Level2Screen() {
    enemySprite.deleteSprite();
}

void Level2Screen::onEnter() {

    feedback.begin();
    hud.setBackground(level2_bg);

    lives          = 3;
    timeLeft       = 15;
    finished       = false;
    playerDead     = false;
    staticDrawn    = false;
    hudDirty       = true;
    needsRender    = true;
    lastEnemySpawn = 0;
    lastMove       = 0;

    for (int i = 0; i < MAX_ENEMIES; i++)
        enemies[i].active = false;
}

GameState Level2Screen::getState() { return GameState::LEVEL2; }

Question Level2Screen::createQuestion() {
    return MathGenerator::generateSubtractionQuestion();
}

void Level2Screen::renderStatic() {
    tft->setSwapBytes(true);
    tft->pushImage(0, 0, 320, 240, (uint16_t*)level2_bg);
    renderPlayer();
}

void Level2Screen::renderPlayer() {
    tft->pushImage(10, 96, 32, 32, (uint16_t*)player_knife1, TFT_BLACK);
}

void Level2Screen::clearGameplayArea() {
    BgUtils::restore(tft, level2_bg, 50, 40, 270, 90);
}
void Level2Screen::clearTimerArea() {
    BgUtils::restore(tft, level2_bg, 0, 130, 320, 30);
}
void Level2Screen::clearQuestionArea() {
    BgUtils::restore(tft, level2_bg, 0, 160, 320, 80);
}

// ─────────────────────────────────────────────────────
// drawEnemy
//
// O sprite tem largura SPR_W + MAX_SPEED (ex: 65px para speed=1).
// A cada frame:
//   - bg é copiado cobrindo a posição NOVA + o rastro (drift px)
//   - enemy é colado com transparência 0x0000 dentro do sprite
//   - pushSprite SEM transparência → uma única escrita SPI
//
// Resultado: rastro coberto + sem flickering.
// ─────────────────────────────────────────────────────
void Level2Screen::drawEnemy(int index, int prevX) {

    int ex    = enemies[index].x;
    int ey    = enemies[index].y;
    int drift = prevX - ex;          // quanto andou (≥ 0, = speed quando moveu)

    // O sprite começa na posição nova menos a margem lateral
    int sx   = ex - 16;
    int sy   = ey - 22;
    int sprW = SPR_W + drift;        // largura real usada este frame
    int sprH = SPR_H;

    // ── 1. Copia bg para o sprite linha a linha ───────
    enemySprite.setSwapBytes(true);

    int csx = sx,    csy = sy;
    int csw = sprW,  csh = sprH;

    // Clamp para não sair da tela
    if (csx < 0)         { csw += csx; csx = 0; }
    if (csy < 0)         { csh += csy; csy = 0; }
    if (csx + csw > 320)   csw = 320 - csx;
    if (csy + csh > 240)   csh = 240 - csy;
    if (csw <= 0 || csh <= 0) return;

    for (int row = 0; row < csh; row++) {
        uint16_t lineBuf[SPR_W + MAX_SPEED];
        memcpy_P(lineBuf,
                 level2_bg + ((csy + row) * 320) + csx,
                 csw * sizeof(uint16_t));

        // x dentro do sprite: 0 quando sx >= 0, ou -sx quando cortado
        enemySprite.pushImage(csx - sx, row, csw, 1, lineBuf);
    }

    // ── 2. Cola o inimigo por cima ────────────────────
    // xPos dentro do sprite = sempre 16 (margem esquerda fixa)
    // porque sx = ex - 16, logo ex - sx = 16
    enemySprite.pushImage(
        16, 22,
        32, 32,
        (uint16_t*)enemy1,
        (uint16_t)0x0000    // transparência só em RAM, sem custo SPI
    );

    // ── 3. Texto ──────────────────────────────────────
    String op = String(enemies[index].question.num1)
              + "-"
              + String(enemies[index].question.num2);

    enemySprite.setTextColor(TFT_WHITE);
    enemySprite.drawCentreString(op, 32, 2, 2); // centro do inimigo = 16+16

    // ── 4. Envia para a tela SEM transparência ────────
    // O bg dentro do sprite já cobre o rastro.
    // pushSprite sem 3º argumento = sem transparência = sem flickering.
    enemySprite.pushSprite(sx, sy);
}

void Level2Screen::eraseEnemy(int index) {
    BgUtils::restore(
        tft, level2_bg,
        enemies[index].x - 16,
        enemies[index].y - 22,
        SPR_W + MAX_SPEED, SPR_H   // mesma largura do sprite
    );
}

void Level2Screen::removeEnemy(int index) {
    eraseEnemy(index);
    enemies[index].active = false;
}

void Level2Screen::spawnEnemy() {

    for (int i = 0; i < MAX_ENEMIES; i++)
        if (enemies[i].active) return;

    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!enemies[i].active) {
            Question q = MathGenerator::generateSubtractionQuestion();

            enemies[i].active   = true;
            enemies[i].x        = 280;
            enemies[i].y        = 96;
            enemies[i].speed    = MAX_SPEED;
            enemies[i].question = q;

            currentQuestion = q;
            questionDirty   = true;
            needsRender     = true;

            renderHUD();
            renderQuestion();
            break;
        }
    }
}

void Level2Screen::checkEnemyAnswer(int answerIndex) {

    int first = -1;
    for (int i = 0; i < MAX_ENEMIES; i++)
        if (enemies[i].active) { first = i; break; }

    if (first == -1) return;

    if (answerIndex == enemies[first].question.correctIndex) {
        feedback.success();
        removeEnemy(first);
        questionDirty = true;
        needsRender   = true;
    } else {
        lives--;
        hudDirty    = true;
        needsRender = true;
        feedback.error();
    }
}

void Level2Screen::checkAnswer(int index) { checkEnemyAnswer(index); }

void Level2Screen::update() {

    if (timer.every(1000)) {
        timeLeft--;
        hudDirty    = true;
        needsRender = true;
    }

    if (millis() - lastEnemySpawn >= spawnInterval) {
        spawnEnemy();
        lastEnemySpawn = millis();
    }

    bool shouldMove = (millis() - lastMove >= MOVE_INTERVAL);
    if (shouldMove) lastMove = millis();

    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!enemies[i].active) continue;

        int prevX = enemies[i].x;

        if (shouldMove)
            enemies[i].x -= enemies[i].speed;

        if (enemies[i].x <= 60) {
            eraseEnemy(i);
            enemies[i].active = false;
            lives--;
            hudDirty      = true;
            questionDirty = true;
            needsRender   = true;
            feedback.error();
        } else {
            drawEnemy(i, prevX);
        }
    }

    if (input->wasPressed(Button::BTN_GREEN))  checkEnemyAnswer(0);
    if (input->wasPressed(Button::BTN_BLUE))   checkEnemyAnswer(1);
    if (input->wasPressed(Button::BTN_YELLOW)) checkEnemyAnswer(2);

    if (lives    <= 0) { finished = true; playerDead = true; }
    if (timeLeft <= 0) { finished = true; }
}

void Level2Screen::render() {

    if (!needsRender) return;

    if (!staticDrawn) {
        renderStatic();
        staticDrawn = true;
    }

    renderHUD();
    renderQuestion();

    needsRender = false;
}

void Level2Screen::renderGameplay() {}