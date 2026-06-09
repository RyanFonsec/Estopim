#pragma once

#include "../screens/BaseScreen.h"

class ScreenManager {

private:

    BaseScreen* currentScreen;

public:

    ScreenManager();

    void setScreen(BaseScreen* screen);

    BaseScreen* getCurrentScreen();

    void resumeScreen(BaseScreen* screen);

    void update();

    void render();
};