#include "FeedbackSystem.h"

#include <Arduino.h>

FeedbackSystem::FeedbackSystem() {

    ledPin = 14;

    buzzerPin = 13;
}

void FeedbackSystem::begin() {

    pinMode(ledPin, OUTPUT);

    pinMode(buzzerPin, OUTPUT);
}

void FeedbackSystem::success() {

    digitalWrite(ledPin, HIGH);

    tone(buzzerPin, 1200);

    delay(100);

    noTone(buzzerPin);

    digitalWrite(ledPin, LOW);
}

void FeedbackSystem::error() {

    digitalWrite(ledPin, HIGH);

    tone(buzzerPin, 300);

    delay(300);

    noTone(buzzerPin);

    digitalWrite(ledPin, LOW);
}

void FeedbackSystem::timeout() {

    for(int i = 0; i < 2; i++) {

        digitalWrite(ledPin, HIGH);

        tone(buzzerPin, 600);

        delay(100);

        digitalWrite(ledPin, LOW);

        noTone(buzzerPin);

        delay(100);
    }
}


//posterior mente mudar o delay, codigo exxperimental, nao usar em producao

//integrar no gameplay com feedback.success() e feedback.error() e feedback.timeout()