#include <stdint.h>
#include <stdio.h>
#include <gd.h>
#include <sys/stat.h>
#include <sys/types.h>


typedef struct {
    uint8_t linesPerCharacter;
    uint8_t bytesPerLine;
    uint8_t startGlyph;
    uint8_t endGlyph;
    uint8_t bitsPerPixel;
} FontHeader;

const char *fontmap[16] = {
    "\x20\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f","\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f",
    "\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f","\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3a\x3b\x3c\x3d\x3e\x3f",
    "\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4a\x4b\x4c\x4d\x4e\x4f","\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5a\x5b\x5c\x5d\x5e\x5f",
    "\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6a\x6b\x6c\x6d\x6e\x6f","\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7a\x7b\x7c\x7d\x7e\x7f",
    "\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f","\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f",
    "\xa0\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\xaf","\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf",
    "\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\xcf","\xd0\xd1\xd2\xd3\xd4\xd5\xd6\xd7\xd8\xd9\xda\xdb\xdc\xdd\xde\xdf",
    "\xe0\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee\xef","\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb\xfc\xfd\xfe\xff"
};

extern void makeFonts();

int main() {
    mkdir("Preview", 0755);
    makeFonts();
    return 0;
}

int stringHeight(const char *text, const uint8_t *font) {
    FontHeader *header = (FontHeader *)font;
    return header->linesPerCharacter;
}

int stringWidth(const char *text, const uint8_t *font) {
    int w = 0;
    if (font == NULL) {
        return 1;
    }
    FontHeader *header = (FontHeader *)font;

    for (const char *t = text; *t; t++) {
        uint8_t c = *t;
        if (c < header->startGlyph) {
            if (c >= 'A' && c <= 'Z') {
                c += ('a' - 'A');
            }
        }
        if (c > header->endGlyph) {
            if (c >= 'a' && c <= 'z') {
                c -= ('a' - 'A');
            }
        }
        if (c >= header->startGlyph && c <= header->endGlyph) {
            uint8_t co = c - header->startGlyph;
            uint32_t charstart = (co * ((header->linesPerCharacter * header->bytesPerLine) + 1)) + sizeof(FontHeader); // Start of character data
            uint8_t charwidth = font[charstart++];
            w += charwidth;
        }
    }
    return w;
}

int drawChar(gdImagePtr img, int x, int y, unsigned char c, const uint8_t *font) {

    FontHeader *header = (FontHeader *)font;

    if (c < header->startGlyph || c > header->endGlyph) {
        return 0;
    }

    c = c - header->startGlyph;

    // Start of this character's data is the character number multiplied by the
    // number of lines in a character (plus one for the character width) multiplied
    // by the number of bytes in a line, and then offset by 4 for the header.
    uint32_t charstart = (c * ((header->linesPerCharacter * header->bytesPerLine) + 1)) + sizeof(FontHeader); // Start of character data
    uint8_t charwidth = font[charstart++]; // The first byte of a block is the width of the character

    uint8_t nCols = 1 << header->bitsPerPixel;
    uint32_t bitmask = nCols - 1;
    int cmap[nCols];

    for (uint8_t i = 0; i < nCols; i++) {
        cmap[i] = gdImageColorAllocate(img, 255 * i / bitmask, 255 * i / bitmask, 255 * i / bitmask);
    }

    for (int8_t lineNumber = 0; lineNumber < header->linesPerCharacter; lineNumber++ ) {
        uint8_t lineData = 0;

        int8_t bitsLeft = -1;
        uint8_t byteNumber = 0;

        for (int8_t pixelNumber = 0; pixelNumber < charwidth; pixelNumber++) {
            if (bitsLeft <= 0) {
                bitsLeft = 8;
                lineData = font[charstart + (lineNumber * header->bytesPerLine) + (header->bytesPerLine - byteNumber - 1)];
                byteNumber++;
            }
            uint32_t pixelValue = lineData & bitmask;

            gdImageSetPixel(img, x + pixelNumber, y + lineNumber, cmap[pixelValue]);

            lineData >>= header->bitsPerPixel;
            bitsLeft -= header->bitsPerPixel;
        }
    }
    return charwidth;
}


void makeFont(const char *family, const char *name, const uint8_t *data) {
    char temp[1024];
    printf("Making font Fonts::%s\n", name);
    int mw = 0;
    for (int i = 0; i < 16; i++) {
        int w = stringWidth(fontmap[i], data);
        if (w > mw) mw = w;
    }
    int lh = stringHeight("a", data);
    int mh = lh * 16;
    printf("    Max width: %d\n", mw);
    printf("    Max height: %d\n", mh);

    gdImagePtr img = gdImageCreateTrueColor(mw, mh);

    for (int l = 0; l < 16; l++) {
        int pos = 0;
        for (int c = 0; c < 16; c++) {
            pos += drawChar(img, pos, l * lh, fontmap[l][c], data);
        }
    }

    sprintf(temp, "Preview/%s", family);
    mkdir(temp, 0755);
    sprintf(temp, "Preview/%s/%s.png", family, name);
    FILE *f = fopen(temp, "w");
    gdImagePng(img, f);
    fclose(f);
    gdImageDestroy(img);
}
