#include "BgUtils.h"

// Buffer estático — um único buffer compartilhado por todos
// os chamadores. Sem custo de heap, sem fragmentação.
uint16_t BgUtils::_lineBuf[320];

void BgUtils::restore(TFT_eSPI* tft,
                      const uint16_t* bg,
                      int x, int y,
                      int w, int h) {
    // Clamp — garante que a janela não sai dos limites da tela
    if (x < 0)       { w += x; x = 0; }
    if (y < 0)       { h += y; y = 0; }
    if (x + w > 320)   w = 320 - x;
    if (y + h > 240)   h = 240 - y;
    if (w <= 0 || h <= 0) return;

    // Abre a janela de escrita uma única vez
    tft->setAddrWindow(x, y, w, h);

    for (int row = 0; row < h; row++) {
        // Stride correto: sempre 320 (largura da imagem original)
        memcpy_P(_lineBuf,
                 bg + ((y + row) * 320) + x,
                 w * sizeof(uint16_t));

        // swapped=true: interpreta RGB565 big-endian do PROGMEM
        tft->pushColors(_lineBuf, w, true);
    }
}