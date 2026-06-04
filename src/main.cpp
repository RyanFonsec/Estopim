#include <Arduino.h>

#include <TFT_eSPI.h>

#include "core/Game.h"

TFT_eSPI tft = TFT_eSPI();

Game game(&tft);

void setup() {
    Serial.begin(115200);

    Serial.println("SETUP INICIO");

    tft.init();

    Serial.println("TFT OK");

    tft.setRotation(1);

    game.begin();
    
    Serial.println("GAME OK");
}

void loop() {

    game.update();

    game.render();
}