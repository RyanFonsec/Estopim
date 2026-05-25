#include "Game.h"

#include "../screens/MenuScreen.h"
#include "../screens/IntroScreen.h"
#include "../screens/Level1Screen.h"
#include "../screens/PauseScreen.h"
#include "../screens/WinScreen.h"
#include "../screens/GameOverScreen.h"
#include "../systems/FeedbackSystem.h"


Game::Game(TFT_eSPI* display)

: menuScreen(display),
  introScreen(display),
  level1Screen(display, &input),
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

        case GameState::LEVEL1:
            screenManager.setScreen(&level1Screen);
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

                changeState(GameState::LEVEL1);
            }

            break;

        // =====================
        // LEVEL1
        // =====================

        case GameState::LEVEL1:

            // PAUSE

            if(input.wasPressed(Button::BTN_BLACK)) {

                changeState(GameState::PAUSE);
            }

         break;

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