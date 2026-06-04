#include "FeedbackSystem.h"
#include <Arduino.h>

FeedbackSystem::FeedbackSystem(
    MusicSystem* musicSystem
) {
    redPin = 21;
    greenPin = 22;
    bluePin = 13;
    buzzerPin = 17;
    buzzerChannel = 0;
    feedbackStart = 0;
    active = false;
    music = musicSystem;
}

void FeedbackSystem::begin() {
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);

    // Inicia com todas as luzes apagadas (HIGH desliga anodo comum)
    clear();

    // PWM BUZZER
    //ledcSetup(buzzerChannel, 2000, 8);
    //ledcAttachPin(buzzerPin, buzzerChannel);
}

void FeedbackSystem::clear() {
    // HIGH apaga as cores no LED Anodo Comum
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, HIGH);

    // Desliga o som do buzzer
    //ledcWriteTone(buzzerChannel, 0);
}

void FeedbackSystem::success() {

    music->playSuccess();
    clear(); // Apaga tudo primeiro

    // LOW acende a cor no LED Anodo Comum
    digitalWrite(greenPin, LOW);

    //ledcWriteTone(buzzerChannel, 1200);

    active = true;

    feedbackStart = millis();
}

void FeedbackSystem::error() {
    music->playError();
    clear(); // Apaga tudo primeiro

    // LOW acende a cor no LED Anodo Comum
    digitalWrite(redPin, LOW);

    //ledcWriteTone(buzzerChannel, 300);

    active = true;

    feedbackStart = millis();
}

void FeedbackSystem::timeout() {
    music->playTimeout();;
    clear(); // Apaga tudo primeiro

    // Vermelho + Verde em LOW cria Amarelo (indicando tempo esgotado)
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);

    //ledcWriteTone(buzzerChannel, 700);

    active = true;

    feedbackStart = millis();
}

void FeedbackSystem::update() {

    if(!active)
        return;

    if(millis() - feedbackStart >= 500) {

        clear();

        active = false;
    }
}
