#include "display.h"
#include "fonts/avgang_mini.h"
#include "fonts/avgang.h"

Display::Display() : m_matrixWidth(64), m_matrixHeight(32), m_matrixChainLength(2), m_maxBrightness(128), m_displayType(DisplayType::DisplayLarge)
{
}

Display::~Display()
{
    // Destructor implementation
}

void Display::init(int displayType)
{
    HUB75_I2S_CFG config(m_matrixWidth, m_matrixHeight, m_matrixChainLength);

    // Configure green and blue channels
    if (displayType != 1)
    {
        config.gpio.b1 = 26;
        config.gpio.b2 = 12;
        config.gpio.g1 = 27;
        config.gpio.g2 = 13;
        m_displayType = DisplayType::DisplaySmall;
    }
    config.clkphase = false;

    dma_display = new MatrixPanel_I2S_DMA(config);
    dma_display->begin();
    dma_display->setFont(&AvgangMini);
    dma_display->clearScreen();
    dma_display->fillScreen(MatrixPanel_I2S_DMA::color565(0, 0, 0));
    dma_display->setTextWrap(false);
}

void Display::clearScreen()
{
    dma_display->clearScreen();
    dma_display->fillScreen(MatrixPanel_I2S_DMA::color565(0, 0, 0));
}

void Display::setFont(Font font)
{
    switch (font)
    {
    case Font::Small:
        dma_display->setFont(&AvgangMini);
        break;
    case Font::Medium:
        dma_display->setFont(&Avgang);
        break;
    case Font::Large:
        dma_display->setFont(&Avgang);
        break;
    default:
        dma_display->setFont(&AvgangMini);
        break;
    }
    m_currentFont = font;
}

Display::Font Display::getFont()
{
    return m_currentFont;
}

uint16_t Display::getDisplayWidth()
{
    return m_matrixWidth * m_matrixChainLength;
}

void Display::setBrightness(uint8_t brightness)
{
    // Limit the brightness to max 128
    if (brightness > m_maxBrightness)
    {
        brightness = m_maxBrightness;
    }
    dma_display->setBrightness(brightness);
}

uint16_t Display::color565(Color color)
{
    switch (color)
    {
    case Color::Black:
        return MatrixPanel_I2S_DMA::color565(0, 0, 0);
    case Color::White:
        return MatrixPanel_I2S_DMA::color565(255, 255, 255);
    case Color::Red:
        return MatrixPanel_I2S_DMA::color565(255, 0, 0);
    case Color::Green:
        return MatrixPanel_I2S_DMA::color565(0, 255, 0);
    case Color::Blue:
        return MatrixPanel_I2S_DMA::color565(0, 0, 255);
    case Color::Yellow:
        return MatrixPanel_I2S_DMA::color565(255, 255, 0);
    case Color::Orange:
        if (m_displayType == DisplayType::DisplaySmall)
            return MatrixPanel_I2S_DMA::color565(255, 140, 0);
        else
            return MatrixPanel_I2S_DMA::color565(255, 100, 0);
    default:
        return MatrixPanel_I2S_DMA::color565(0, 0, 0);
    }
}

void Display::printText(String text, int16_t x, int16_t y, Color color)
{
    sanitizeText(text);
    y += fontSizeInPixels(m_currentFont); // Shift the text down to the baseline based on the font size
    dma_display->setTextSize(1);          // size 1 == 8 pixels or 12 pixels high depending on the font
    dma_display->setTextColor(this->color565(color));
    dma_display->setCursor(x, y);
    dma_display->print(text);
}

void Display::printText(String text, int16_t line, Color color)
{
    int16_t x = 0;
    int16_t y = line * fontSizeInPixels(m_currentFont);
    printText(text, x, y, color);
}

void Display::printTextRightAligned(String text, int16_t line, Color color)
{
    int16_t x = dma_display->width();
    int16_t y = line * fontSizeInPixels(m_currentFont);
    printTextRightAligned(text, x, y, color);
}

void Display::printTextRightAligned(String text, int16_t x, int16_t y, Color color)
{
    sanitizeText(text);
    y += fontSizeInPixels(m_currentFont); // Shift the text down to the baseline based on the font size
    dma_display->setTextSize(1);          // size 1 == 8 pixels or 12 pixels high depending on the font
    dma_display->setTextColor(this->color565(color));

    int16_t xOne, yOne;
    uint16_t w, h;
    dma_display->getTextBounds(text, 0, 0, &xOne, &yOne, &w, &h);

    int xPosition = x - w;
    dma_display->setCursor(xPosition, y);
    dma_display->print(text);
}

void Display::sanitizeText(String &text)
{
    text.replace("å", "|");
    text.replace("ä", "{");
    text.replace("ö", "}");
    text.replace("Å", "]");
    text.replace("Ä", "[");
    text.replace("Ö", "^");
}

uint8_t Display::fontSizeInPixels(Font font)
{
    switch (font)
    {
    case Font::Small:
        return AvgangMini.yAdvance;
    case Font::Medium:
        return Avgang.yAdvance;
    case Font::Large:
        return Avgang.yAdvance;
    default:
        return 8;
    }
}
uint8_t Display::getFontHeight()
{
    return fontSizeInPixels(m_currentFont);
}

void Display::printTextCentered(String text, Color color)
{
    dma_display->clearScreen();
    dma_display->setTextSize(1);
    dma_display->setTextWrap(false);
    dma_display->setTextColor(this->color565(color));

    int16_t xOne, yOne;
    uint16_t w, h;
    dma_display->getTextBounds(text, 0, 0, &xOne, &yOne, &w, &h);

    int xPosition = dma_display->width() / 2 - w / 2 + 1;
    dma_display->setCursor(xPosition, (m_matrixHeight / 2) + (fontSizeInPixels(m_currentFont) / 4));
    dma_display->print(text);
}

void Display::demo()
{
    dma_display->clearScreen();
    dma_display->fillScreen(color565(Color::Black));
    dma_display->setTextWrap(false);

    dma_display->setTextSize(1); // size 1 == 8 pixels high
    dma_display->setTextColor(color565(Color::Orange));
    dma_display->setCursor(0, fontSizeInPixels(m_currentFont));
    dma_display->print("21:00 Stockholm C");

    dma_display->setCursor(0, fontSizeInPixels(m_currentFont) * 2);
    dma_display->print("21:06 Falun");

    dma_display->setCursor(0, fontSizeInPixels(m_currentFont) * 3);
    dma_display->print("21:05 Eskilstuna");

    dma_display->setCursor(0, fontSizeInPixels(m_currentFont) * 4);
    dma_display->print("22:03 Uppsala");
}