#pragma once

#include <Arduino.h>

enum class Button {

    BTN_GREEN,
    BTN_BLUE,
    BTN_YELLOW,
    BTN_BLACK,
    BTN_WHITE

};

class InputSystem {

private:

    int buttonPins[5];

    bool currentState[5];

    bool previousState[5];

public:

    InputSystem();

    void begin();

    void update();

    bool isPressed(Button button);

    bool wasPressed(Button button);

};

/*

Agora o jogo  usa:

input.isPressed(Button::BTN_GREEN)

e NÃO:

digitalRead(27)
*/