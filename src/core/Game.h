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
#include "../screens/Tutorial2Screen.h"
#include "../screens/Tutorial3Screen.h"
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
    BaseScreen* pausedScreen;

    GameState pausedState;

    // =====================================
    // SCREENS (Como Ponteiros)
    // =====================================
    MenuScreen* menuScreen;
    TutorialScreen* tutorialScreen;
    Tutorial2Screen* tutorial2Screen;
    Tutorial3Screen* tutorial3Screen;
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