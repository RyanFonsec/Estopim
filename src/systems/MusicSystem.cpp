#include "MusicSystem.h"

#include <Arduino.h>

// =====================================
// MUSICA DE EXPLORAÇÃO
// =====================================

const int explorationMelody[] = {

    330, // E4
    392, // G4
    440, // A4
    392,

    330,
    294,
    330,
    392,

    440,
    494,
    440,
    392
};

const int explorationSize =
    sizeof(explorationMelody)
    / sizeof(explorationMelody[0]);

// =====================================
// MUSICA DE BATALHA
// =====================================

const int battleMelody[] = {

    523,
    494,
    523,
    659,

    587,
    523,
    494,
    440
};

const int battleSize =
    sizeof(battleMelody)
    / sizeof(battleMelody[0]);

// =====================================

MusicSystem::MusicSystem() {

    currentMode =
        MusicMode::EXPLORATION;

    buzzerPin = 17;

    channel = 1;

    currentNote = 0;

    noteStart = 0;

    paused = false;

    playingEffect = false;

    effectStart = 0;

    currentEffect = EffectType::NONE;

    effectStep = 0;

    effectTimer = 0;
}

// =====================================

void MusicSystem::begin() {

    ledcSetup(
        channel,
        1000,
        8
    );

    ledcAttachPin(
        buzzerPin,
        channel
    );

    noteStart = millis();

    ledcWriteTone(
        channel,
        explorationMelody[0]
    );

    Serial.println(
        "Music started"
    );
}

// =====================================

void MusicSystem::setMode(
    MusicMode mode
) {

    currentMode = mode;

    currentNote = 0;

    noteStart = millis();

    if(mode ==
       MusicMode::EXPLORATION) {

        ledcWriteTone(
            channel,
            explorationMelody[0]
        );
    }
    else {

        ledcWriteTone(
            channel,
            battleMelody[0]
        );
    }
}

// =====================================

void MusicSystem::update() {

    if(paused)
        return;

    // =============================
    // FEEDBACK
    // =============================

    if(playingEffect)
{
    unsigned long elapsed =
        millis() - effectTimer;

    int freq = 0;

    switch(currentEffect)
    {
        case EffectType::SUCCESS:
            freq = 1200;
            break;

        case EffectType::ERROR:
            freq = 300;
            break;

        case EffectType::TIMEOUT:
            freq = 700;
            break;

        default:
            break;
    }

    switch(effectStep)
    {
        case 0:

            ledcWriteTone(
                channel,
                freq
            );

            effectStep++;

            effectTimer = millis();

            break;

        case 1:

            if(elapsed >= 100)
            {
                ledcWriteTone(
                    channel,
                    0
                );

                effectStep++;

                effectTimer = millis();
            }

            break;

        case 2:

            if(elapsed >= 50)
            {
                ledcWriteTone(
                    channel,
                    freq
                );

                effectStep++;

                effectTimer = millis();
            }

            break;

        case 3:

            if(elapsed >= 100)
            {
                playingEffect = false;

                currentEffect =
                    EffectType::NONE;

                noteStart =
                    millis();
            }

            break;
    }

    return;
}

    // =============================
    // MÚSICA NORMAL
    // =============================

    if(
        millis()
        - noteStart
        >= 600
    ) {

        if(currentMode ==
           MusicMode::EXPLORATION) {

            currentNote++;

            if(
                currentNote
                >= explorationSize
            ) {

                currentNote = 0;
            }

            ledcWriteTone(
                channel,
                explorationMelody[currentNote]
            );
        }
        else {

            currentNote++;

            if(
                currentNote
                >= battleSize
            ) {

                currentNote = 0;
            }

            ledcWriteTone(
                channel,
                battleMelody[currentNote]
            );
        }

        noteStart = millis();
    }
}

// =====================================

void MusicSystem::pause() {

    paused = true;

    ledcWriteTone(
        channel,
        0
    );
}

// =====================================

void MusicSystem::resume() {

    paused = false;

    noteStart = millis();

    if(currentMode ==
       MusicMode::EXPLORATION) {

        ledcWriteTone(
            channel,
            explorationMelody[currentNote]
        );
    }
    else {

        ledcWriteTone(
            channel,
            battleMelody[currentNote]
        );
    }
}

// =====================================

void MusicSystem::playSuccess()
{
    currentEffect =
        EffectType::SUCCESS;

    effectStep = 0;

    playingEffect = true;

    effectTimer = millis();
}

// =====================================

void MusicSystem::playError()
{
    currentEffect =
        EffectType::ERROR;

    effectStep = 0;

    playingEffect = true;

    effectTimer = millis();
}

// =====================================

void MusicSystem::playTimeout()
{
    currentEffect =
        EffectType::TIMEOUT;

    effectStep = 0;

    playingEffect = true;

    effectTimer = millis();
}