#pragma once

#include "../core/BaseLevelScreen.h"
#include "../game/Enemy.h"

class Level2Screen : public BaseLevelScreen {

public:

    Level2Screen(TFT_eSPI* display, InputSystem* input);

    void onEnter()  override;
    void update()   override;
    void render()   override;
    GameState getState() override;

protected:

    Question createQuestion() override;

    void renderStatic()       override;
    void renderPlayer();
    void renderGameplay()     override;
    void clearGameplayArea()  override;
    void clearTimerArea()     override;
    void clearQuestionArea()  override;
    void checkAnswer(int index) override;

private:

    static const int MAX_ENEMIES = 1;

    Enemy enemies[MAX_ENEMIES];

    unsigned long lastEnemySpawn;
    unsigned long spawnInterval;

    void spawnEnemy();
    void stepAndDrawEnemies();   // apaga → move → desenha em único tick
    void updateEnemies();        // stub — delegado para stepAndDrawEnemies
    void renderEnemies();        // stub — delegado para stepAndDrawEnemies
    void removeEnemy(int index);
    void checkEnemyAnswer(int answerIndex);
};