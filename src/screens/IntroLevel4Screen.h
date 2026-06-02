#pragma once

#include "BaseScreen.h"

#include <TFT_eSPI.h>

class IntroLevel4Screen : public BaseScreen {

private:

    TFT_eSPI* tft;

public:

    IntroLevel4Screen(TFT_eSPI* display);

    void onEnter() override;

    void onExit() override;

    void update() override;

    void render() override;

    GameState getState() override;

};