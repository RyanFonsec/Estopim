#include "ScreenManager.h"

ScreenManager::ScreenManager() {

    currentScreen = nullptr;
}

void ScreenManager::setScreen(BaseScreen* screen) {

    if(currentScreen != nullptr) {

        currentScreen->onExit();
    }

    currentScreen = screen;

    currentScreen->onEnter();
}

BaseScreen* ScreenManager::getCurrentScreen() {

    return currentScreen;
}

void ScreenManager::update() {

    if(currentScreen != nullptr) {

        currentScreen->update();
    }
}

void ScreenManager::render() {

    if(currentScreen != nullptr &&
       currentScreen->shouldRender()) {

        currentScreen->render();

        currentScreen->rendered();
    }
}

void ScreenManager::resumeScreen(
    BaseScreen* screen
) {
    currentScreen = screen;
}