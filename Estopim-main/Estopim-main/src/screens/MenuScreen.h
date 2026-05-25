#pragma once

#include "BaseScreen.h"

#include "../core/GameState.h"

#include <TFT_eSPI.h>

class MenuScreen : public BaseScreen {

private:

    TFT_eSPI* tft;

public:

    MenuScreen(TFT_eSPI* display);

    void onEnter() override;

    void onExit() override;

    void update() override;

    void render() override;

    GameState getState() override;
};