#include "HUD.h"

#include "../assets/hud/heart_icon.h"
#include "../assets/hud/player_icon.h"

// ───────────────────────────────────────────────────────
// BUFFER AUXILIAR
// ───────────────────────────────────────────────────────

static uint16_t _hudLineBuf[320];

// ───────────────────────────────────────────────────────
// restoreBgRect
//
// Restaura uma área do background PROGMEM corretamente.
// Evita bug visual do pushImage com offset.
// ───────────────────────────────────────────────────────

static void restoreBgRect(
    TFT_eSPI* tft,
    const uint16_t* bg,
    int x,
    int y,
    int w,
    int h
) {

    if(!bg) return;

    // ============================================
    // CLAMP
    // ============================================

    if(x < 0) {

        w += x;
        x = 0;
    }

    if(y < 0) {

        h += y;
        y = 0;
    }

    if(x + w > 320) {

        w = 320 - x;
    }

    if(y + h > 240) {

        h = 240 - y;
    }

    if(w <= 0 || h <= 0) {

        return;
    }

    // ============================================
    // RESTORE
    // ============================================

    tft->setAddrWindow(x, y, w, h);

    for(int row = 0; row < h; row++) {

        const uint16_t* src =
            bg + ((y + row) * 320) + x;

        memcpy_P(
            _hudLineBuf,
            src,
            w * sizeof(uint16_t)
        );

        tft->pushColors(
            _hudLineBuf,
            w,
            true
        );
    }
}

// ───────────────────────────────────────────────────────
// CONSTRUTOR
// ───────────────────────────────────────────────────────

HUD::HUD(TFT_eSPI* display) {

    tft = display;

    currentBg = nullptr;

    lives = -1;

    timeLeft = -1;

    livesDirty = true;

    timeDirty = true;
}

// ───────────────────────────────────────────────────────
// SETTERS
// ───────────────────────────────────────────────────────

void HUD::setLives(int value) {

    if(lives != value) {

        lives = value;

        livesDirty = true;
    }
}

void HUD::setTime(int value) {

    if(timeLeft != value) {

        timeLeft = value;

        timeDirty = true;
    }
}

void HUD::setBackground(const uint16_t* bg) {

    currentBg = bg;
}

// ───────────────────────────────────────────────────────
// RENDER PRINCIPAL
// ───────────────────────────────────────────────────────

void HUD::render() {

    renderLives();

    renderTimeBar();
}

// ───────────────────────────────────────────────────────
// VIDAS
// ───────────────────────────────────────────────────────

void HUD::renderLives() {

    if(!livesDirty) {

        return;
    }

    if(!currentBg) {

        return;
    }

    // ============================================
    // RESTAURA BG
    // ============================================

    restoreBgRect(
        tft,
        currentBg,
        0,
        0,
        120,
        30
    );

    // ============================================
    // PLAYER ICON
    // ============================================

    tft->pushImage(
        5,
        3,
        24,
        24,
        player_icon,
        TFT_BLACK
    );

    // ============================================
    // CORAÇÕES
    // ============================================

    for(int i = 0; i < lives; i++) {

        tft->pushImage(
            35 + (i * 18),
            6,
            16,
            16,
            heart_icon,
            TFT_BLACK
        );
    }

    livesDirty = false;
}

// ───────────────────────────────────────────────────────
// TIMER
// ───────────────────────────────────────────────────────

void HUD::renderTimeBar() {

    if(!timeDirty) {

        return;
    }

    if(!currentBg) {

        return;
    }

    // ============================================
    // RESTAURA BG
    // ============================================

    restoreBgRect(
        tft,
        currentBg,
        0,
        130,
        320,
        30
    );

    // ============================================
    // TEXTO
    // ============================================

    tft->setTextColor(TFT_WHITE);

    tft->drawRightString(
        String(timeLeft) + " SEG",
        310,
        136,
        2
    );

    // ============================================
    // BORDA
    // ============================================

    tft->drawRect(
        10,
        145,
        220,
        10,
        TFT_WHITE
    );

    // ============================================
    // TAMANHO DA BARRA
    // TIMER PADRÃO = 15 SEG
    // ============================================

    int width = map(
        timeLeft,
        0,
        15,
        0,
        216
    );

    if(width < 0) {

        width = 0;
    }

    // ============================================
    // BARRA VERDE
    // ============================================

    if(width > 0) {

        tft->fillRect(
            12,
            147,
            width,
            6,
            TFT_GREEN
        );
    }

    timeDirty = false;
}