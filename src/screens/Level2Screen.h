#pragma once

#include "../core/BaseLevelScreen.h"
#include "../game/Enemy.h"

class Level2Screen : public BaseLevelScreen {

private:

    static const int MAX_ENEMIES = 5;

    Enemy enemies[MAX_ENEMIES];

    unsigned long lastEnemySpawn;

    unsigned long spawnInterval;

    void spawnEnemy();

    void updateEnemies();

    void renderEnemies();

    void renderOperations();

    void removeEnemy(int index);

    void checkEnemyAnswer(int answerIndex);

public:

    Level2Screen(
        TFT_eSPI* display,
        InputSystem* in
    );

    GameState getState() override;

    void onEnter() override;
    
    void update() override;

protected:

    Question createQuestion() override;

    void renderStatic() override;

    void clearQuestionArea() override;

    void clearGameplayArea() override;

    void clearTimerArea() override;

    void renderGameplay() override;

    void checkAnswer(int index) override;
};