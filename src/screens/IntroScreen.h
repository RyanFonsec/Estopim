#pragma once

#include "BaseScreen.h"

#include <TFT_eSPI.h>

class IntroScreen : public BaseScreen {

private:

    TFT_eSPI* tft;

public:

    IntroScreen(TFT_eSPI* display);

    void onEnter() override;

    void onExit() override;

    void update() override;

    void render() override;

    GameState getState() override;

};