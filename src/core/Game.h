#pragma once

#include <TFT_eSPI.h>

#include "../systems/InputSystem.h"

#include "../core/ScreenManager.h"

#include "../core/GameState.h"

#include "../screens/MenuScreen.h"
#include "../screens/IntroScreen.h"
#include "../screens/Level1Screen.h"
#include "../screens/Level2Screen.h"
#include "../screens/PauseScreen.h"
#include "../screens/WinScreen.h"
#include "../screens/GameOverScreen.h"
#include "../systems/FeedbackSystem.h"

class Game {

private:

    TFT_eSPI* tft;

    InputSystem input;

    ScreenManager screenManager;

    FeedbackSystem feedback;

    GameState currentState;

    // =====================================
    // SCREENS
    // =====================================

    MenuScreen menuScreen;

    IntroScreen introScreen;

    Level1Screen level1Screen;

    Level2Screen level2Screen;

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
/*
#define TFT_CS    15  // Conectado ao D15 azul
#define TFT_RST    4  // Conectado ao D4 roxo
#define TFT_DC     2  // Conectado ao D2 (Data/Command) cinza
#define TFT_MOSI  23  // Conectado ao D23 (Hardware SPI MOSI/SDI) laranja
#define TFT_SCK   18  // Conectado ao D18 (Hardware SPI SCK) marrom
#define TFT_MISO  19  // Conectado ao D19 (Hardware SPI MISO) preto

3.3 vermelho
gnd marrom
*/