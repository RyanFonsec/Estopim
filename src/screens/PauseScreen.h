#pragma once

#include "BaseScreen.h"

#include <TFT_eSPI.h>

class PauseScreen : public BaseScreen {

private:

    TFT_eSPI* tft;

public:

    PauseScreen(TFT_eSPI* display);

    void onEnter() override;

    void onExit() override;

    void update() override;

    void render() override;

    GameState getState() override;
};