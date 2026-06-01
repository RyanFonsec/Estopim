#pragma once
#include <TFT_eSPI.h>
#include <Arduino.h>

// ─────────────────────────────────────────────────────────────
// BgUtils — utilitário para restaurar janelas de backgrounds
// armazenados em PROGMEM (stride fixo de 320px).
//
// Por que não usar pushImage com offset diretamente?
// O TFT_eSPI usa o 'w' da janela como stride interno ao ler
// PROGMEM, não o width original da imagem (320). Resultado:
// da segunda linha em diante os pixels são lidos do lugar
// errado → borragem. Esta função resolve isso copiando
// cada linha individualmente via memcpy_P.
//
// Uso:
//   BgUtils::restore(tft, level2_bg, x, y, w, h);
// ─────────────────────────────────────────────────────────────

class BgUtils {
public:
    // Restaura o trecho (x, y, w, h) de um bg PROGMEM 320×240
    // diretamente na tela. Faz clamp automático nas bordas.
    static void restore(TFT_eSPI* tft,
                        const uint16_t* bg,
                        int x, int y,
                        int w, int h);

private:
    // Buffer de linha compartilhado — evita malloc no loop
    static uint16_t _lineBuf[320];
};