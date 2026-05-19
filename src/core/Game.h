#pragma once

#include <TFT_eSPI.h>

#include "../systems/InputSystem.h"

#include "../core/ScreenManager.h"

#include "../core/GameState.h"

#include "../screens/MenuScreen.h"
#include "../screens/IntroScreen.h"
#include "../screens/Level1Screen.h"
#include "../screens/PauseScreen.h"
#include "../screens/WinScreen.h"
#include "../screens/GameOverScreen.h"

class Game {

private:

    TFT_eSPI* tft;

    InputSystem input;

    ScreenManager screenManager;

    GameState currentState;

    // =====================================
    // SCREENS
    // =====================================

    MenuScreen menuScreen;

    IntroScreen introScreen;

    Level1Screen level1Screen;

    PauseScreen pauseScreen;

    WinScreen winScreen;

    GameOverScreen gameOverScreen;

public:

    Game(TFT_eSPI* display);

    void begin();

    void update();

    void render();

    void changeState(GameState newState);
};