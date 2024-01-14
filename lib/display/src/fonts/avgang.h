#include <Adafruit_GFX.h>

const uint8_t Avgang_Bitmaps[] PROGMEM = {
    0xFF, 0xFC, 0xF0, 0xFF, 0xFC, 0xF0, 0x6D, 0xE0, 0xFF, 0xC0, 0xF0, 0x7B,
    0x3C, 0xF3, 0xCF, 0x3C, 0xF3, 0xCD, 0xE0, 0x37, 0xF3, 0x33, 0x33, 0x33,
    0x7B, 0x30, 0xC3, 0x18, 0xE6, 0x30, 0xC3, 0xF0, 0x7B, 0x30, 0xC3, 0x38,
    0x30, 0xC3, 0xCD, 0xE0, 0x0E, 0x3C, 0xDB, 0x3C, 0x78, 0xFF, 0x83, 0x06,
    0x0C, 0x00, 0xFF, 0x0C, 0x30, 0xF8, 0x30, 0xF3, 0xCD, 0xE0, 0x7B, 0x3C,
    0x30, 0xFB, 0x3C, 0xF3, 0xCD, 0xE0, 0xFC, 0x30, 0xC6, 0x18, 0xC3, 0x0C,
    0x30, 0xC0, 0x7B, 0x3C, 0xF3, 0x79, 0xEC, 0xF3, 0xCD, 0xE0, 0x7B, 0x3C,
    0xF3, 0xCD, 0xF0, 0xC3, 0xCD, 0xE0, 0xF3, 0xC0, 0xFF, 0xF0, 0x3F, 0xFC,
    0x00, 0x7D, 0x8C, 0x18, 0x30, 0xC3, 0x0C, 0x00, 0x30, 0x60, 0x00, 0x38,
    0x6C, 0xC6, 0xC6, 0xC6, 0xFE, 0xC6, 0xC6, 0xC6, 0xC6, 0xFC, 0xC6, 0xC6,
    0xC6, 0xFC, 0xC6, 0xC6, 0xC6, 0xC6, 0xFC, 0x7C, 0xC6, 0xC6, 0xC6, 0xC0,
    0xC0, 0xC6, 0xC6, 0xC6, 0x7C, 0xFC, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6,
    0xC6, 0xC6, 0xFC, 0xFE, 0xC0, 0xC0, 0xC0, 0xF8, 0xC0, 0xC0, 0xC0, 0xC0,
    0xFE, 0xFE, 0xC0, 0xC0, 0xC0, 0xF0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x7C,
    0xC6, 0xC0, 0xC0, 0xC0, 0xDE, 0xC6, 0xC6, 0xC6, 0x7E, 0xC6, 0xC6, 0xC6,
    0xC6, 0xFE, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xDB, 0x6D, 0xB6, 0xD8, 0x00,
    0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0xC0, 0xCE,
    0xDC, 0xF8, 0xF0, 0xE0, 0xE0, 0xF0, 0xF8, 0xDC, 0xCE, 0xC0, 0xC0, 0xC0,
    0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xFE, 0xFE, 0xC6, 0xEE, 0xFE, 0xD6, 0xC6,
    0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xE6, 0xE6, 0xD6, 0xD6, 0xCE,
    0xCE, 0xC6, 0xC6, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6,
    0x7C, 0xFC, 0xC6, 0xC6, 0xC6, 0xFC, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x7C,
    0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xD6, 0xDE, 0x7C, 0x0E, 0xFC, 0xC6,
    0xC6, 0xC6, 0xFC, 0xCC, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0xC6, 0xC0, 0xC0,
    0x70, 0x1C, 0x06, 0x06, 0xC6, 0x7C, 0xFF, 0x0C, 0x06, 0x03, 0x01, 0x80,
    0xC0, 0x60, 0x30, 0x18, 0x0C, 0x00, 0xCD, 0x9B, 0x36, 0x6C, 0xD9, 0xB3,
    0x66, 0xCC, 0xF0, 0x00, 0xCD, 0x9B, 0x36, 0x6C, 0xD9, 0xB3, 0x66, 0x78,
    0x60, 0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xD6, 0xFE, 0xFE, 0xC6,
    0xC6, 0xC6, 0xC6, 0x6C, 0x38, 0x38, 0x6C, 0xC6, 0xC6, 0xC6, 0xCD, 0x9B,
    0x36, 0x67, 0x86, 0x0C, 0x18, 0x30, 0x60, 0x00, 0xFE, 0xFE, 0x06, 0x0C,
    0x18, 0x30, 0x60, 0xC0, 0xFE, 0xFE, 0xFF, 0x7B, 0x30, 0xDF, 0xCF, 0x3C,
    0xDF, 0xC3, 0x0F, 0xB3, 0xCF, 0x3C, 0xF3, 0xCF, 0xE0, 0x7B, 0x3C, 0xF0,
    0xC3, 0x3C, 0xDE, 0x0C, 0x37, 0xF3, 0xCF, 0x3C, 0xF3, 0xCD, 0xF0, 0x7B,
    0x3C, 0xFF, 0xC3, 0x0C, 0xDE, 0x3B, 0x19, 0xE6, 0x31, 0x8C, 0x63, 0x00,
    0x01, 0xFC, 0xF3, 0xCF, 0x3C, 0xD3, 0x7C, 0x3C, 0xDE, 0xC3, 0x0F, 0xB3,
    0xCF, 0x3C, 0xF3, 0xCF, 0x30, 0xCF, 0xFF, 0xF0, 0x61, 0xB6, 0xDB, 0x6F,
    0x00, 0xC3, 0x0C, 0xF6, 0xF3, 0x8E, 0x3C, 0xDB, 0x30, 0xFF, 0xFF, 0xF0,
    0xFB, 0xB3, 0x3C, 0xCF, 0x33, 0xCC, 0xF3, 0x3C, 0xCF, 0x33, 0xFB, 0x3C,
    0xF3, 0xCF, 0x3C, 0xF3, 0x7B, 0x3C, 0xF3, 0xCF, 0x3C, 0xDE, 0xFB, 0x3C,
    0xF3, 0xCF, 0x3C, 0xFE, 0xC3, 0x0C, 0x00, 0x7F, 0x3C, 0xF3, 0xCF, 0x3C,
    0xF3, 0x7C, 0x30, 0xC0, 0xDF, 0xF9, 0x8C, 0x63, 0x18, 0x7B, 0x3C, 0x1C,
    0x38, 0x3C, 0xDE, 0x66, 0xF6, 0x66, 0x66, 0x63, 0xCF, 0x3C, 0xF3, 0xCF,
    0x3C, 0xDE, 0xCF, 0x3C, 0xF3, 0xCF, 0x37, 0x8C, 0xCC, 0xF3, 0x3C, 0xCF,
    0x33, 0xCC, 0xF3, 0x37, 0xF8, 0xCC, 0xCF, 0x37, 0x8C, 0x31, 0xEC, 0xF3,
    0xCF, 0x3C, 0xF3, 0xCF, 0x37, 0xC3, 0x0D, 0xE0, 0xFC, 0x30, 0xC6, 0x31,
    0x8C, 0x3F, 0x6C, 0x00, 0xE3, 0x6C, 0x7F, 0xF1, 0xE3, 0xC7, 0x8C, 0x00,
    0x38, 0xD8, 0xE3, 0x6C, 0x7F, 0xF1, 0xE3, 0xC7, 0x8C, 0x00, 0x6C, 0x01,
    0xF6, 0x3C, 0x78, 0xF1, 0xE3, 0xC6, 0xF8, 0x00, 0x6C, 0x07, 0xB3, 0x0D,
    0xFC, 0xF3, 0xCD, 0xF0, 0x31, 0x27, 0xB3, 0x0D, 0xFC, 0xF3, 0xCD, 0xF0,
    0x48, 0x07, 0xB3, 0xCF, 0x3C, 0xF3, 0xCD, 0xE0};

const GFXglyph Avgang_Glyphs[] PROGMEM = {
    {0, 1, 0, 3, 0, -1},     // 0x20 ' '
    {3, 2, 10, 4, 0, -10},   // 0x21 '!'
    {0, 0, 0, 0, 0, 0},      // 0x22 '"'
    {0, 0, 0, 0, 0, 0},      // 0x23 '#'
    {0, 0, 0, 0, 0, 0},      // 0x24 '$'
    {0, 0, 0, 0, 0, 0},      // 0x25 '%'
    {0, 0, 0, 0, 0, 0},      // 0x26 '&'
    {0, 0, 0, 0, 0, 0},      // 0x27 '''
    {0, 0, 0, 0, 0, 0},      // 0x28 '('
    {0, 0, 0, 0, 0, 0},      // 0x29 ')'
    {0, 0, 0, 0, 0, 0},      // 0x2A '*'
    {0, 0, 0, 0, 0, 0},      // 0x2B '+'
    {6, 3, 4, 4, 0, -2},     // 0x2C ','
    {8, 5, 2, 6, 0, -5},     // 0x2D '-'
    {10, 2, 2, 3, 0, -2},    // 0x2E '.'
    {0, 0, 0, 0, 0, 0},      // 0x2F '/'
    {11, 6, 10, 7, 0, -10},  // 0x30 '0'
    {19, 4, 10, 5, 0, -10},  // 0x31 '1'
    {24, 6, 10, 7, 0, -10},  // 0x32 '2'
    {32, 6, 10, 7, 0, -10},  // 0x33 '3'
    {40, 7, 10, 8, 0, -10},  // 0x34 '4'
    {50, 6, 10, 7, 0, -10},  // 0x35 '5'
    {58, 6, 10, 7, 0, -10},  // 0x36 '6'
    {66, 6, 10, 7, 0, -10},  // 0x37 '7'
    {74, 6, 10, 7, 0, -10},  // 0x38 '8'
    {82, 6, 10, 7, 0, -10},  // 0x39 '9'
    {90, 2, 5, 3, 0, -7},    // 0x3A ':'
    {0, 0, 0, 0, 0, 0},      // 0x3B ';'
    {0, 0, 0, 0, 0, 0},      // 0x3C '<'
    {92, 6, 5, 7, 0, -7},    // 0x3D '='
    {0, 0, 0, 0, 0, 0},      // 0x3E '>'
    {97, 7, 10, 8, 0, -10},  // 0x3F '?'
    {0, 0, 0, 0, 0, 0},      // 0x40 '@'
    {107, 8, 10, 8, 0, -10}, // 0x41 'A'
    {117, 8, 10, 8, 0, -10}, // 0x42 'B'
    {127, 8, 10, 8, 0, -10}, // 0x43 'C'
    {137, 8, 10, 8, 0, -10}, // 0x44 'D'
    {147, 8, 10, 8, 0, -10}, // 0x45 'E'
    {157, 8, 10, 8, 0, -10}, // 0x46 'F'
    {167, 8, 10, 8, 0, -10}, // 0x47 'G'
    {177, 8, 10, 8, 0, -10}, // 0x48 'H'
    {187, 3, 10, 3, 0, -10}, // 0x49 'I'
    {192, 8, 11, 4, 0, -10}, // 0x4A 'J'
    {203, 8, 10, 8, 0, -10}, // 0x4B 'K'
    {213, 8, 10, 8, 0, -10}, // 0x4C 'L'
    {223, 8, 10, 8, 0, -10}, // 0x4D 'M'
    {233, 8, 10, 8, 0, -10}, // 0x4E 'N'
    {243, 8, 10, 8, 0, -10}, // 0x4F 'O'
    {253, 8, 10, 8, 0, -10}, // 0x50 'P'
    {263, 8, 11, 8, 0, -10}, // 0x51 'Q'
    {274, 8, 10, 8, 0, -10}, // 0x52 'R'
    {284, 8, 10, 8, 0, -10}, // 0x53 'S'
    {294, 9, 10, 9, 0, -10}, // 0x54 'T'
    {306, 7, 10, 7, 0, -10}, // 0x55 'U'
    {316, 7, 10, 7, 0, -10}, // 0x56 'V'
    {326, 8, 10, 8, 0, -10}, // 0x57 'W'
    {336, 8, 10, 8, 0, -10}, // 0x58 'X'
    {346, 7, 10, 7, 0, -10}, // 0x59 'Y'
    {356, 8, 10, 8, 0, -10}, // 0x5A 'Z'
    {0, 0, 0, 0, 0, 0},      // 0x5B '['
    {0, 0, 0, 0, 0, 0},      // 0x5C '\'
    {0, 0, 0, 0, 0, 0},      // 0x5D ']'
    {0, 0, 0, 0, 0, 0},      // 0x5E '^'
    {366, 4, 2, 4, 0, -2},   // 0x5F '_'
    {0, 0, 0, 0, 0, 0},      // 0x60 '`'
    {367, 6, 8, 7, 0, -8},   // 0x61 'a'
    {373, 6, 10, 7, 0, -10}, // 0x62 'b'
    {381, 6, 8, 7, 0, -8},   // 0x63 'c'
    {387, 6, 10, 7, 0, -10}, // 0x64 'd'
    {395, 6, 8, 7, 0, -8},   // 0x65 'e'
    {401, 5, 10, 6, 0, -10}, // 0x66 'f'
    {408, 6, 12, 7, 0, -9},  // 0x67 'g'
    {417, 6, 10, 7, 0, -10}, // 0x68 'h'
    {425, 2, 10, 3, 0, -10}, // 0x69 'i'
    {428, 3, 11, 4, 0, -10}, // 0x6A 'j'
    {433, 6, 10, 7, 0, -10}, // 0x6B 'k'
    {441, 2, 10, 3, 0, -10}, // 0x6C 'l'
    {444, 10, 8, 11, 0, -8}, // 0x6D 'm'
    {454, 6, 8, 7, 0, -8},   // 0x6E 'n'
    {460, 6, 8, 7, 0, -8},   // 0x6F 'o'
    {466, 6, 11, 7, 0, -8},  // 0x70 'p'
    {475, 6, 11, 7, 0, -9},  // 0x71 'q'
    {484, 5, 8, 6, 0, -8},   // 0x72 'r'
    {489, 6, 8, 7, 0, -8},   // 0x73 's'
    {495, 4, 10, 5, 0, -10}, // 0x74 't'
    {500, 6, 8, 7, 0, -8},   // 0x75 'u'
    {506, 6, 8, 7, 0, -8},   // 0x76 'v'
    {512, 10, 8, 11, 0, -8}, // 0x77 'w'
    {522, 6, 8, 7, 0, -8},   // 0x78 'x'
    {528, 6, 10, 7, 0, -8},  // 0x79 'y'
    {536, 6, 8, 7, 0, -8},   // 0x7A 'z'
    {0, 0, 0, 0, 0, 0},      // 0x7B '{'
    {0, 0, 0, 0, 0, 0},      // 0x7C '|'
    {0, 0, 0, 0, 0, 0},      // 0x7D '}'
    {0, 0, 0, 0, 0, 0},      // 0x7E '~'
    {0, 0, 0, 0, 0, 0},      // 0x7F 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0x80 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0x81 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0x82 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0x83 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0x84 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0x85 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0x86 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0x87 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0x88 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0x89 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0x8A 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0x8B 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0x8C 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0x8D 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0x8E 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0x8F 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0x90 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0x91 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0x92 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0x93 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0x94 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0x95 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0x96 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0x97 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0x98 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0x99 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0x9A 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0x9B 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0x9C 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0x9D 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0x9E 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0x9F 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0xA0 ' '
    {0, 0, 0, 0, 0, 0},      // 0xA1 '¡'
    {0, 0, 0, 0, 0, 0},      // 0xA2 '¢'
    {0, 0, 0, 0, 0, 0},      // 0xA3 '£'
    {0, 0, 0, 0, 0, 0},      // 0xA4 '¤'
    {0, 0, 0, 0, 0, 0},      // 0xA5 '¥'
    {0, 0, 0, 0, 0, 0},      // 0xA6 '¦'
    {0, 0, 0, 0, 0, 0},      // 0xA7 '§'
    {0, 0, 0, 0, 0, 0},      // 0xA8 '¨'
    {0, 0, 0, 0, 0, 0},      // 0xA9 '©'
    {0, 0, 0, 0, 0, 0},      // 0xAA 'ª'
    {0, 0, 0, 0, 0, 0},      // 0xAB '«'
    {0, 0, 0, 0, 0, 0},      // 0xAC '¬'
    {0, 0, 0, 0, 0, 0},      // 0xAD 'non-printable'
    {0, 0, 0, 0, 0, 0},      // 0xAE '®'
    {0, 0, 0, 0, 0, 0},      // 0xAF '¯'
    {0, 0, 0, 0, 0, 0},      // 0xB0 '°'
    {0, 0, 0, 0, 0, 0},      // 0xB1 '±'
    {0, 0, 0, 0, 0, 0},      // 0xB2 '²'
    {0, 0, 0, 0, 0, 0},      // 0xB3 '³'
    {0, 0, 0, 0, 0, 0},      // 0xB4 '´'
    {0, 0, 0, 0, 0, 0},      // 0xB5 'µ'
    {0, 0, 0, 0, 0, 0},      // 0xB6 '¶'
    {0, 0, 0, 0, 0, 0},      // 0xB7 '·'
    {0, 0, 0, 0, 0, 0},      // 0xB8 '¸'
    {0, 0, 0, 0, 0, 0},      // 0xB9 '¹'
    {0, 0, 0, 0, 0, 0},      // 0xBA 'º'
    {0, 0, 0, 0, 0, 0},      // 0xBB '»'
    {0, 0, 0, 0, 0, 0},      // 0xBC '¼'
    {0, 0, 0, 0, 0, 0},      // 0xBD '½'
    {0, 0, 0, 0, 0, 0},      // 0xBE '¾'
    {0, 0, 0, 0, 0, 0},      // 0xBF '¿'
    {0, 0, 0, 0, 0, 0},      // 0xC0 'À'
    {0, 0, 0, 0, 0, 0},      // 0xC1 'Á'
    {0, 0, 0, 0, 0, 0},      // 0xC2 'Â'
    {0, 0, 0, 0, 0, 0},      // 0xC3 'Ã'
    {542, 7, 10, 8, 0, -10}, // 0xC4 'Ä'
    {552, 7, 10, 8, 0, -10}, // 0xC5 'Å'
    {0, 0, 0, 0, 0, 0},      // 0xC6 'Æ'
    {0, 0, 0, 0, 0, 0},      // 0xC7 'Ç'
    {0, 0, 0, 0, 0, 0},      // 0xC8 'È'
    {0, 0, 0, 0, 0, 0},      // 0xC9 'É'
    {0, 0, 0, 0, 0, 0},      // 0xCA 'Ê'
    {0, 0, 0, 0, 0, 0},      // 0xCB 'Ë'
    {0, 0, 0, 0, 0, 0},      // 0xCC 'Ì'
    {0, 0, 0, 0, 0, 0},      // 0xCD 'Í'
    {0, 0, 0, 0, 0, 0},      // 0xCE 'Î'
    {0, 0, 0, 0, 0, 0},      // 0xCF 'Ï'
    {0, 0, 0, 0, 0, 0},      // 0xD0 'Ð'
    {0, 0, 0, 0, 0, 0},      // 0xD1 'Ñ'
    {0, 0, 0, 0, 0, 0},      // 0xD2 'Ò'
    {0, 0, 0, 0, 0, 0},      // 0xD3 'Ó'
    {0, 0, 0, 0, 0, 0},      // 0xD4 'Ô'
    {0, 0, 0, 0, 0, 0},      // 0xD5 'Õ'
    {562, 7, 10, 8, 0, -10}, // 0xD6 'Ö'
    {0, 0, 0, 0, 0, 0},      // 0xD7 '×'
    {0, 0, 0, 0, 0, 0},      // 0xD8 'Ø'
    {0, 0, 0, 0, 0, 0},      // 0xD9 'Ù'
    {0, 0, 0, 0, 0, 0},      // 0xDA 'Ú'
    {0, 0, 0, 0, 0, 0},      // 0xDB 'Û'
    {0, 0, 0, 0, 0, 0},      // 0xDC 'Ü'
    {0, 0, 0, 0, 0, 0},      // 0xDD 'Ý'
    {0, 0, 0, 0, 0, 0},      // 0xDE 'Þ'
    {0, 0, 0, 0, 0, 0},      // 0xDF 'ß'
    {0, 0, 0, 0, 0, 0},      // 0xE0 'à'
    {0, 0, 0, 0, 0, 0},      // 0xE1 'á'
    {0, 0, 0, 0, 0, 0},      // 0xE2 'â'
    {0, 0, 0, 0, 0, 0},      // 0xE3 'ã'
    {572, 6, 10, 7, 0, -10}, // 0xE4 'ä'
    {580, 6, 10, 7, 0, -10}, // 0xE5 'å'
    {0, 0, 0, 0, 0, 0},      // 0xE6 'æ'
    {0, 0, 0, 0, 0, 0},      // 0xE7 'ç'
    {0, 0, 0, 0, 0, 0},      // 0xE8 'è'
    {0, 0, 0, 0, 0, 0},      // 0xE9 'é'
    {0, 0, 0, 0, 0, 0},      // 0xEA 'ê'
    {0, 0, 0, 0, 0, 0},      // 0xEB 'ë'
    {0, 0, 0, 0, 0, 0},      // 0xEC 'ì'
    {0, 0, 0, 0, 0, 0},      // 0xED 'í'
    {0, 0, 0, 0, 0, 0},      // 0xEE 'î'
    {0, 0, 0, 0, 0, 0},      // 0xEF 'ï'
    {0, 0, 0, 0, 0, 0},      // 0xF0 'ð'
    {0, 0, 0, 0, 0, 0},      // 0xF1 'ñ'
    {0, 0, 0, 0, 0, 0},      // 0xF2 'ò'
    {0, 0, 0, 0, 0, 0},      // 0xF3 'ó'
    {0, 0, 0, 0, 0, 0},      // 0xF4 'ô'
    {0, 0, 0, 0, 0, 0},      // 0xF5 'õ'
    {588, 6, 10, 7, 0, -10}  // 0xF6 'ö'
};

const GFXfont Avgang PROGMEM = {(uint8_t *)Avgang_Bitmaps, (GFXglyph *)Avgang_Glyphs, 0x20, 0xF6, 12};