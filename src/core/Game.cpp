#include "Game.h"

// Construtor limpo: Inicializa os ponteiros como nulos
// para não gastar memória antes da hora (evita o crash global)
Game::Game(TFT_eSPI* display) {
    tft = display;
    
    menuScreen = nullptr;
    tutorialScreen = nullptr;
    introScreen = nullptr;
    introLevel1Screen = nullptr;
    level1Screen = nullptr;
    introLevel2Screen = nullptr;
    level2Screen = nullptr;
    introLevel3Screen = nullptr;
    level3Screen = nullptr;
    introLevel4Screen = nullptr;
    level4Screen = nullptr;
    pauseScreen = nullptr;
    winScreen = nullptr;
    gameOverScreen = nullptr;
}

// Destrutor: Garante a liberação de memória Heap
Game::~Game() {
    delete menuScreen;
    delete tutorialScreen;
    delete introScreen;
    delete introLevel1Screen;
    delete level1Screen;
    delete introLevel2Screen;
    delete level2Screen;
    delete introLevel3Screen;
    delete level3Screen;
    delete introLevel4Screen;
    delete level4Screen;
    delete pauseScreen;
    delete winScreen;
    delete gameOverScreen;
}

// =====================================
// BEGIN
// =====================================
void Game::begin() {
    input.begin();
    feedback.begin();

    // Instancia as telas dinamicamente na RAM (Heap) após o tft.init() ter rodado
    menuScreen = new MenuScreen(tft);
    tutorialScreen = new TutorialScreen(tft);
    introScreen = new IntroScreen(tft);
    introLevel1Screen = new IntroLevel1Screen(tft);
    level1Screen = new Level1Screen(tft, &input);
    introLevel2Screen = new IntroLevel2Screen(tft);
    level2Screen = new Level2Screen(tft, &input);
    introLevel3Screen = new IntroLevel3Screen(tft);
    level3Screen = new Level3Screen(tft, &input);
    introLevel4Screen = new IntroLevel4Screen(tft);
    level4Screen = new Level4Screen(tft, &input);
    pauseScreen = new PauseScreen(tft);
    winScreen = new WinScreen(tft);
    gameOverScreen = new GameOverScreen(tft);

    changeState(GameState::LEVEL4);
}

// =====================================
// CHANGE STATE
// =====================================
void Game::changeState(GameState newState) {
    currentState = newState;
    input.reset();

    switch(currentState) {
        case GameState::MENU:
            screenManager.setScreen(menuScreen); 
            break;

        case GameState::TUTORIAL:
            screenManager.setScreen(tutorialScreen);
            break;

        case GameState::INTRO:
            screenManager.setScreen(introScreen);
            break;
        
        case GameState::INTROLV1:
            screenManager.setScreen(introLevel1Screen);
            break;

        case GameState::LEVEL1:
            screenManager.setScreen(level1Screen);
            break;

        case GameState::INTROLV2:
            screenManager.setScreen(introLevel2Screen);
            break;

        case GameState::LEVEL2:
            screenManager.setScreen(level2Screen);
            break;

        case GameState::INTROLV3:
            screenManager.setScreen(introLevel3Screen);
            break;

        case GameState::LEVEL3:
            screenManager.setScreen(level3Screen);
            break;

        case GameState::INTROLV4:
            screenManager.setScreen(introLevel4Screen);
            break;

        case GameState::LEVEL4:
            screenManager.setScreen(level4Screen);
            break;

        case GameState::PAUSE:
            screenManager.setScreen(pauseScreen);
            break;

        case GameState::WIN:
            screenManager.setScreen(winScreen);
            break;

        case GameState::GAME_OVER:
            screenManager.setScreen(gameOverScreen);
            break;

        default:
            break;
    }
}

// =====================================
// UPDATE
// =====================================
void Game::update() {
    input.update();

    switch(currentState) {
        case GameState::MENU:
            if(input.wasPressed(Button::BTN_GREEN)) {
                changeState(GameState::TUTORIAL);
            }
            break;
        
        case GameState::TUTORIAL:
            if(input.wasPressed(Button::BTN_GREEN)) {
                changeState(GameState::INTRO);
            }
            break;

        case GameState::INTRO:
            if(input.wasPressed(Button::BTN_GREEN)) {
                changeState(GameState::INTROLV1);
            }
            break;

        case GameState::INTROLV1:
            if(input.wasPressed(Button::BTN_GREEN)) {
                changeState(GameState::LEVEL1);
            }
            break;

        case GameState::LEVEL1:
        {
            if(input.wasPressed(Button::BTN_BLACK)) {
                changeState(GameState::PAUSE);
            }

            Level1Screen* level = static_cast<Level1Screen*>(screenManager.getCurrentScreen());
            if(level->isFinished()) {
                if(level->isPlayerDead()) {
                    changeState(GameState::GAME_OVER);
                } else {
                    changeState(GameState::INTROLV2);
                }
            }
            break;
        }

        case GameState::INTROLV2:
            if(input.wasPressed(Button::BTN_GREEN)) {
                tft->fillScreen(TFT_BLACK);
                changeState(GameState::LEVEL2);
            }
            break;

        case GameState::LEVEL2:
        {
            if(input.wasPressed(Button::BTN_BLACK)) {
                changeState(GameState::PAUSE);
            }

            Level2Screen* level = static_cast<Level2Screen*>(screenManager.getCurrentScreen());
            if(level->isFinished()) {
                if(level->isPlayerDead()) {
                    changeState(GameState::GAME_OVER);
                } else {
                    changeState(GameState::INTROLV3);
                }
            }
            break;
        }

        case GameState::INTROLV3:
            if(input.wasPressed(Button::BTN_GREEN)) {
                tft->fillScreen(TFT_BLACK);
                changeState(GameState::LEVEL3);
            }
            break;
        
        case GameState::LEVEL3:
        {
            if(input.wasPressed(Button::BTN_BLACK)) {
                changeState(GameState::PAUSE);
            }

            Level3Screen* level =
                static_cast<Level3Screen*>(
                    screenManager.getCurrentScreen()
                );

            if(level->isFinished()) {

                if(level->isPlayerDead()) {

                    changeState(GameState::GAME_OVER);
                }
                else {

                    changeState(GameState::INTROLV4);
                }
            }

            break;
        }

        case GameState::INTROLV4:
            if(input.wasPressed(Button::BTN_GREEN)) {
                tft->fillScreen(TFT_BLACK);
                changeState(GameState::LEVEL4);
            }
            break;

        case GameState::LEVEL4:
        {
            Level4Screen* level =
                static_cast<Level4Screen*>(
                    screenManager.getCurrentScreen()
                );

            if(level->isFinished()) {

                if(level->isPlayerDead()) {

                    changeState(
                        GameState::GAME_OVER
                    );
                }
                else {

                    changeState(
                        GameState::WIN
                    );
                }
            }

            break;
        }

        case GameState::PAUSE:
            if(input.wasPressed(Button::BTN_BLACK)) {
                changeState(GameState::LEVEL1);
            }
            break;

        default:
            break;
    }

    if(input.wasPressed(Button::BTN_WHITE)) {
        ESP.restart();
    }

    screenManager.update();
}

// =====================================
// RENDER
// =====================================
void Game::render() {
    screenManager.render();
}