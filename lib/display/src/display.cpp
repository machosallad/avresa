#include "display.h"

Display::Display()
{
    HUB75_I2S_CFG config(m_matrixWidth, m_matrixHeight, m_matrixChainLength);
    // Configure green and blue channels
    config.gpio.b1 = 26;
    config.gpio.b2 = 12;
    config.gpio.g1 = 27;
    config.gpio.g2 = 13;
    config.clkphase = false;

    dma_display = new MatrixPanel_I2S_DMA(config);
    dma_display->begin();

    dma_display->clearScreen();
    dma_display->fillScreen(MatrixPanel_I2S_DMA::color565(0, 0, 0));
    dma_display->setTextWrap(false);
}

Display::~Display()
{
    // Destructor implementation
}

void Display::clearScreen()
{
    dma_display->clearScreen();
    dma_display->fillScreen(MatrixPanel_I2S_DMA::color565(0, 0, 0));
}

uint16_t Display::color565(Color color)
{
    switch (color)
    {
    case BLACK:
        return MatrixPanel_I2S_DMA::color565(0, 0, 0);
    case WHITE:
        return MatrixPanel_I2S_DMA::color565(255, 255, 255);
    case RED:
        return MatrixPanel_I2S_DMA::color565(255, 0, 0);
    case GREEN:
        return MatrixPanel_I2S_DMA::color565(0, 255, 0);
    case BLUE:
        return MatrixPanel_I2S_DMA::color565(0, 0, 255);
    case YELLOW:
        return MatrixPanel_I2S_DMA::color565(255, 255, 0);
    case DARK_ORANGE:
        return MatrixPanel_I2S_DMA::color565(255, 140, 0);
    default:
        return MatrixPanel_I2S_DMA::color565(0, 0, 0);
    }
}

void Display::printText(String text, int16_t x, int16_t y, Color color)
{
    sanitizeText(text);
    dma_display->setTextSize(1); // size 1 == 8 pixels high
    dma_display->setTextColor(this->color565(color));
    dma_display->setCursor(x, y);
    dma_display->print(text);
}

void Display::sanitizeText(String &text)
{
    text.replace("ä", "a");
    text.replace("ö", "o");
    text.replace("Å", "A");
    text.replace("Ä", "A");
    text.replace("Ö", "O");
}

void Display::printTextCentered(String text, Color color)
{
    dma_display->clearScreen();
    dma_display->setTextSize(2);
    dma_display->setTextWrap(false);
    dma_display->setTextColor(this->color565(color));

    int16_t xOne, yOne;
    uint16_t w, h;
    dma_display->getTextBounds(text, 0, 0, &xOne, &yOne, &w, &h);

    int xPosition = dma_display->width() / 2 - w / 2 + 1;
    dma_display->setCursor(xPosition, 8); // 8 is the middle of the screen
    dma_display->print(text);
}

void Display::demo()
{
    dma_display->clearScreen();
    dma_display->fillScreen(color565(BLACK));
    dma_display->setTextWrap(false);

    dma_display->setTextSize(1); // size 1 == 8 pixels high
    dma_display->setTextColor(color565(DARK_ORANGE));
    dma_display->setCursor(0, 0);
    dma_display->print("21:00 Stockholm C");

    dma_display->setCursor(0, 8);
    dma_display->print("21:06 Falun");

    dma_display->setCursor(0, 16);
    dma_display->print("21:05 Eskilstuna");

    dma_display->setCursor(0, 24);
    dma_display->print("22:03 Uppsala");
}