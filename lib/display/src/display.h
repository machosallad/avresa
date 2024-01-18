#ifndef DISPLAY_H
#define DISPLAY_H

#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

class Display
{
public:
    Display();
    ~Display();

    enum Color
    {
        BLACK,
        WHITE,
        RED,
        GREEN,
        BLUE,
        YELLOW,
        DARK_ORANGE
    };

    enum Font
    {
        SMALL,
        MEDIUM,
        LARGE
    };

    void demo();
    void printText(String text, int16_t x, int16_t y, Color color = Color::DARK_ORANGE);
    void printTextRightAligned(String text, int16_t x, int16_t y, Color color = Color::DARK_ORANGE);
    void printTextCentered(String text, Color color = Color::DARK_ORANGE);
    uint8_t getFontHeight();
    void clearScreen();
    void setFont(Font font);
    Font getFont();
    uint16_t getDisplayWidth();

    uint16_t color565(Color color);

private:
    void sanitizeText(String &text);
    uint8_t fontSizeInPixels(Font font);
    MatrixPanel_I2S_DMA *dma_display = nullptr;
    Font m_currentFont = Font::SMALL;
    const uint16_t m_matrixWidth = 64;
    const uint16_t m_matrixHeight = 32;
    const uint16_t m_matrixChainLength = 2;
};

#endif // DISPLAY_H