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
        AMBER,
        ORANGE,
        NUMBER_OF_COLORS
    };

    enum Font
    {
        SMALL,
        MEDIUM,
        LARGE,
        NUMBER_OF_FONTS
    };

    void init(int uuid);
    void demo();
    void printText(String text, int16_t x, int16_t y, Color color = Color::AMBER);
    void printTextRightAligned(String text, int16_t x, int16_t y, Color color = Color::AMBER);
    void printTextCentered(String text, Color color = Color::AMBER);
    uint8_t getFontHeight();
    void clearScreen();
    void setFont(Font font);
    Font getFont();
    uint16_t getDisplayWidth();
    void setBrightness(uint8_t brightness);

    uint16_t color565(Color color);

private:
    void sanitizeText(String &text);
    uint8_t fontSizeInPixels(Font font);
    MatrixPanel_I2S_DMA *dma_display = nullptr;
    Font m_currentFont = Font::SMALL;
    const uint16_t m_matrixWidth;
    const uint16_t m_matrixHeight;
    const uint16_t m_matrixChainLength;
    const uint8_t m_maxBrightness;
};

#endif // DISPLAY_H