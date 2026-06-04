#include "MusicSystem.h"

#include <Arduino.h>

const int melody[] = {
    262, // C4
    294, // D4
    330, // E4
    349, // F4
    392, // G4
    440, // A4
    494, // B4
    523  // C5
};

const int melodySize = 8;

MusicSystem::MusicSystem() {

    buzzerPin = 17;
    channel = 1;

    currentNote = 0;
    noteStart = 0;

    paused = false;

    playingEffect = false;
    effectStart = 0;
}

void MusicSystem::begin() {

    ledcSetup(channel, 1000, 8);

    ledcAttachPin(
        buzzerPin,
        channel
    );

    noteStart = millis();

    ledcWriteTone(
        channel,
        melody[currentNote]
    );

    Serial.println("Music started");
}

void MusicSystem::update() {

    if(paused)
        return;

    // ==========================
    // EFEITO TOCANDO
    // ==========================
    if(playingEffect) {

        if(millis() - effectStart >= 500) {

            playingEffect = false;

            // volta imediatamente para a música
            ledcWriteTone(
                channel,
                melody[currentNote]
            );

            noteStart = millis();
        }

        return;
    }

    // ==========================
    // MÚSICA NORMAL
    // ==========================
    if(millis() - noteStart >= 250) {

        currentNote++;

        if(currentNote >= melodySize) {

            currentNote = 0;
        }

        ledcWriteTone(
            channel,
            melody[currentNote]
        );

        noteStart = millis();
    }
}

void MusicSystem::pause() {

    paused = true;

    ledcWriteTone(channel, 0);
}

void MusicSystem::resume() {

    paused = false;

    noteStart = millis();

    ledcWriteTone(
        channel,
        melody[currentNote]
    );
}

void MusicSystem::playSuccess() {

    ledcWriteTone(channel, 1200);

    playingEffect = true;

    effectStart = millis();
}

void MusicSystem::playError() {

    ledcWriteTone(channel, 300);

    playingEffect = true;

    effectStart = millis();
}

void MusicSystem::playTimeout() {

    ledcWriteTone(channel, 700);

    playingEffect = true;

    effectStart = millis();
}