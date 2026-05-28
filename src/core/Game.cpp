#include "Game.h"

#include "../screens/MenuScreen.h"
#include "../screens/IntroScreen.h"
#include "../screens/IntroLevel1Screen.h"
#include "../screens/Level1Screen.h"
#include "../screens/IntroLevel2Screen.h"
#include "../screens/Level2Screen.h"
#include "../screens/PauseScreen.h"
#include "../screens/WinScreen.h"
#include "../screens/GameOverScreen.h"
#include "../systems/FeedbackSystem.h"


Game::Game(TFT_eSPI* display)

: menuScreen(display),
  introScreen(display),
  introLevel1Screen(display),
  level1Screen(display, &input),
  introLevel2Screen(display),
  level2Screen(display, &input),
  pauseScreen(display),
  winScreen(display),
  gameOverScreen(display)

{
    tft = display;
}

// =====================================
// CHANGE STATE
// =====================================

void Game::changeState(GameState newState) {

    currentState = newState;

    input.reset();

    switch(currentState) {

        case GameState::MENU:
            screenManager.setScreen(&menuScreen);
            break;

        case GameState::INTRO:
            screenManager.setScreen(&introScreen);
            break;
        
        case GameState::INTROLV1:
            screenManager.setScreen(&introLevel1Screen);
            break;
        case GameState::LEVEL1:
            screenManager.setScreen(&level1Screen);
            break;
        case GameState::INTROLV2:
            screenManager.setScreen(&introLevel2Screen);
            break;
        case GameState::LEVEL2:
            screenManager.setScreen(&level2Screen);
            break;

        case GameState::PAUSE:
            screenManager.setScreen(&pauseScreen);
            break;

        case GameState::WIN:
            screenManager.setScreen(&winScreen);
            break;

        case GameState::GAME_OVER:
            screenManager.setScreen(&gameOverScreen);
            break;

        default:
            break;
    }
}

// =====================================
// BEGIN
// =====================================

void Game::begin() {

    input.begin();
    feedback.begin();
    changeState(GameState::MENU);
}

// =====================================
// UPDATE
// =====================================

void Game::update() {

    input.update();

    switch(currentState) {

        // =====================
        // MENU
        // =====================

        case GameState::MENU:

            if(input.wasPressed(Button::BTN_GREEN)) {

                changeState(GameState::INTRO);
            }

            break;

        // =====================
        // INTRO
        // =====================

        case GameState::INTRO:

            if(input.wasPressed(Button::BTN_GREEN)) {

                changeState(GameState::INTROLV1);
            }

        // =====================
        // INTRO LEVEL 1
        // =====================

        case GameState::INTROLV1:

            if(input.wasPressed(Button::BTN_GREEN)) {

                changeState(GameState::LEVEL1);
            }

            break;

            break;

        // =====================
        // LEVEL1
        // =====================

        case GameState::LEVEL1:
        {
            // PAUSE

            if(input.wasPressed(Button::BTN_BLACK)) {

                changeState(GameState::PAUSE);
            }

            Level1Screen* level =

            static_cast<Level1Screen*>(
                screenManager.getCurrentScreen()
            );

            if(level->isFinished()) {

                if(level->isPlayerDead()) {

                    changeState(GameState::GAME_OVER);
                }
                else {

                    changeState(GameState::INTROLV2);
                }
            }

         break;
        }

        // =====================
        // INTRO LEVEL 2
        // =====================

        case GameState::INTROLV2:

            if(input.wasPressed(Button::BTN_GREEN)) {

                changeState(GameState::LEVEL2);
            }

        // =====================
        // LEVEL2
        // =====================

        case GameState::LEVEL2:
        {
            // PAUSE

            if(input.wasPressed(Button::BTN_BLACK)) {

                changeState(GameState::PAUSE);
            }

            Level2Screen* level =

            static_cast<Level2Screen*>(
                screenManager.getCurrentScreen()
            );

        if(level->isFinished()) {

            if(level->isPlayerDead()) {

                changeState(GameState::GAME_OVER);
            }
        }

         break;
        }

        // =====================
        // PAUSE
        // =====================

        case GameState::PAUSE:

            if(input.wasPressed(Button::BTN_BLACK)) {

                changeState(GameState::LEVEL1);
            }

            break;

        default:
            break;
    }

    // =====================
    // RESET GLOBAL
    // =====================

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