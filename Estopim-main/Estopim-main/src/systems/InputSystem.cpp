#include "InputSystem.h"

InputSystem::InputSystem() {

    buttonPins[0] = 27;
    buttonPins[1] = 26;
    buttonPins[2] = 25;
    buttonPins[3] = 33;
    buttonPins[4] = 32;
}

void InputSystem::begin() {

    for(int i = 0; i < 5; i++) {

        pinMode(buttonPins[i], INPUT);

        currentState[i] = false;

        previousState[i] = false;
    }
}

void InputSystem::update() {

    for(int i = 0; i < 5; i++) {

        previousState[i] = currentState[i];

        currentState[i] = digitalRead(buttonPins[i]);
    }
}

bool InputSystem::isPressed(Button button) {

    return currentState[(int)button];
}

bool InputSystem::wasPressed(Button button) {

    return currentState[(int)button] &&
           !previousState[(int)button];
}

// função criada para resolver o erro de mudar de estado já apertando o botão
void InputSystem::reset(){
      for(int i = 0; i < 5; i++) {
        // Lê o estado atual e força o anterior a ser igual
        currentState[i] = digitalRead(buttonPins[i]);
        previousState[i] = currentState[i]; 
    }
}