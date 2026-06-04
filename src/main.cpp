#include <Arduino.h>

#include <TFT_eSPI.h>

#include "core/Game.h"

TFT_eSPI tft = TFT_eSPI();

Game game(&tft);

void setup() {
    tft.init();

    tft.setRotation(1);

    game.begin();
}

void loop() {

    game.update();

    game.render();
}