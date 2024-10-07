#ifndef DISPLAY_H
#define DISPLAY_H

#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

class Display
{
public:
    Display(uint8_t brightness);
    ~Display();

    enum class Color
    {
        Black,
        White,
        Red,
        Green,
        Blue,
        Yellow,
        Amber,
        Orange,
        NumberOfColors
    };

    enum class Font
    {
        Small,
        Medium,
        Large,
        NumberOfFonts
    };

    enum class DisplayType
    {
        DisplaySmall,
        DisplayLarge,
        NumberOfDisplayTypes
    };

    enum class Line
    {
        Line1 = 0,
        Line2 = 1,
        Line3 = 2,
        Line4 = 3,
        NumberOfLines = 4
    };

    void
    init(int displayType);
    void demo();
    void printText(String text, int16_t x, int16_t y, Color color = Color::Orange, bool clearScreen = false);
    void printText(String text, int16_t line, Color color = Color::Orange, bool clearScreen = false);
    void printText(String text, Line line, Color color = Color::Orange, bool clearScreen = false, uint8_t paddingTop = 0, uint8_t paddingLeft = 0);
    void printTextRightAligned(String text, int16_t line, Color color = Color::Orange);
    void printTextRightAligned(String text, int16_t x, int16_t y, Color color = Color::Orange);
    void printTextCentered(String text, Color color = Color::Orange);
    uint8_t getFontHeight();
    void clearScreen();
    void setFont(Font font);
    Font getFont();
    uint16_t getDisplayWidth();
    uint16_t getDisplayHeight();
    void setBrightness(uint8_t brightness);
    void fillColorPercentage(uint8_t percentage, Color color = Color::Green);
    void fillColorPercentage(uint8_t percentage, Color color, int16_t y, int16_t height, uint8_t paddingTop = 0);
    void fillColorPercentage(uint8_t percentage, Color color, Line line, uint8_t paddingTop = 0);
    void setPixel(int16_t x, int16_t y, Color color);
    void drawQrCode(String text, int16_t xOffset, int16_t yOffset, Color color);

    uint16_t color565(Color color);

private:
    void sanitizeText(String &text);
    uint8_t fontSizeInPixels(Font font);
    MatrixPanel_I2S_DMA *dma_display = nullptr;
    Font m_currentFont = Font::Small;
    const uint16_t m_matrixWidth;
    const uint16_t m_matrixHeight;
    const uint16_t m_matrixChainLength;
    const uint8_t m_maxBrightness;
    DisplayType m_displayType;
};

#endif // DISPLAY_H