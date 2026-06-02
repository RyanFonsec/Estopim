#pragma once

#include "BaseScreen.h"

#include <TFT_eSPI.h>

class TutorialScreen: public BaseScreen {

private:

    TFT_eSPI* tft;

public:

    TutorialScreen(TFT_eSPI* display);

    void onEnter() override;

    void onExit() override;

    void update() override;

    void render() override;

    GameState getState() override;

};