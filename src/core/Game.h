#pragma once

#include <TFT_eSPI.h>
#include "../systems/InputSystem.h"
#include "../core/ScreenManager.h"
#include "../core/GameState.h"
#include "../systems/FeedbackSystem.h"
#include "../systems/MusicSystem.h"

// Includes das telas
#include "../screens/MenuScreen.h"
#include "../screens/IntroScreen.h"
#include "../screens/TutorialScreen.h"
#include "../screens/IntroLevel1Screen.h"
#include "../screens/Level1Screen.h"
#include "../screens/IntroLevel2Screen.h"
#include "../screens/Level2Screen.h"
#include "../screens/IntroLevel3Screen.h"
#include "../screens/Level3Screen.h"
#include "../screens/IntroLevel4Screen.h"
#include "../screens/Level4Screen.h"
#include "../screens/PauseScreen.h"
#include "../screens/WinScreen.h"
#include "../screens/GameOverScreen.h"

class Game {

private:
    TFT_eSPI* tft;
    InputSystem input;
    ScreenManager screenManager;
    MusicSystem music;
    FeedbackSystem* feedback;
    GameState currentState;

    // =====================================
    // SCREENS (Como Ponteiros)
    // =====================================
    MenuScreen* menuScreen;
    TutorialScreen* tutorialScreen;
    IntroScreen* introScreen;
    IntroLevel1Screen* introLevel1Screen;
    Level1Screen* level1Screen;
    IntroLevel2Screen* introLevel2Screen;
    Level2Screen* level2Screen;
    IntroLevel3Screen* introLevel3Screen;
    Level3Screen* level3Screen;
    IntroLevel4Screen* introLevel4Screen;
    Level4Screen* level4Screen;
    PauseScreen* pauseScreen;
    WinScreen* winScreen;
    GameOverScreen* gameOverScreen;
    

public:
    Game(TFT_eSPI* display);
    ~Game(); // Destrutor para liberar memória se necessário

    void begin();
    void update();
    void render();
    void changeState(GameState newState);
};