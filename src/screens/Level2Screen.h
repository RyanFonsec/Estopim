#pragma once

#include "../core/BaseLevelScreen.h"
#include "../game/Enemy.h"
#include "../systems/BgUtils.h"
#include <TFT_eSPI.h>

class Level2Screen : public BaseLevelScreen {

public:

    Level2Screen(TFT_eSPI* display, InputSystem* input);
    ~Level2Screen();

    void onEnter()       override;
    void update()        override;
    void render()        override;
    GameState getState() override;

protected:

    Question createQuestion()   override;
    void renderStatic()         override;
    void renderPlayer();
    void renderGameplay()       override;
    void clearGameplayArea()    override;
    void clearTimerArea()       override;
    void clearQuestionArea()    override;
    void checkAnswer(int index) override;

private:

    static const int MAX_ENEMIES   = 1;
    static const int MAX_SPEED     = 3;   // pixels por passo — muda aqui para ajustar velocidade
    static const int MOVE_INTERVAL = 20;  // ms entre passos — muda aqui para ajustar velocidade
    static const int SPR_W         = 64;  // 16px margem + 32px sprite + 16px margem
    static const int SPR_H         = 54;  // 22px texto   + 32px sprite

    Enemy       enemies[MAX_ENEMIES];
    TFT_eSprite enemySprite;              // criado com SPR_W + MAX_SPEED

    unsigned long lastEnemySpawn;
    unsigned long spawnInterval;
    unsigned long lastMove;

    void spawnEnemy();
    void drawEnemy(int index, int prevX);
    void eraseEnemy(int index);
    void removeEnemy(int index);
    void checkEnemyAnswer(int answerIndex);
};