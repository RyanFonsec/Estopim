#pragma once

#include <TFT_eSPI.h>

#include "ScreenManager.h"
#include "GameState.h"

#include "../systems/InputSystem.h"

class Game {

private:

    TFT_eSPI* tft;

    ScreenManager screenManager;

    InputSystem input;

    GameState currentState;

public:

    Game(TFT_eSPI* display);

    void begin();

    void update();

    void render();

    void changeState(GameState newState);
};