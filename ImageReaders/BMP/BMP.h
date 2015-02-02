/*
 * Copyright (c) 2014, Majenko Technologies
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 * 
 * * Neither the name of Majenko Technologies nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _BMP_H
#define _BMP_H

#include <DisplayCore.h>

// BMP file parser

struct BitmapFileHeader {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfBitmapOffset;
} __attribute__((packed));

struct BitmapInfoHeader {
    uint32_t biSize;
    int32_t  biWidth;
    int32_t  biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t  biXPelsPerMeter;
    int32_t  biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
    uint32_t biMaskRed;
    uint32_t biMaskGreen;
    uint32_t biMaskBlue;
    uint32_t biMaskAlpha;
} __attribute__((packed));

struct BitmapPixel24 {
    uint8_t b;
    uint8_t g;
    uint8_t r;
} __attribute__((packed));

struct BitmapPixel32 {
    union {
        uint32_t value;
        struct {
            uint8_t a;
            uint8_t b;
            uint8_t g;
            uint8_t r;
        } __attribute__((packed));
    } __attribute__((packed));
} __attribute__((packed));

class BMP : public Image {
    public: // should be private
        const char *_data;
        const char *_image;
        struct BitmapFileHeader *_header;
        struct BitmapInfoHeader *_info;
        struct BitmapPixel32 *_palette;
        uint16_t _paletteSize;

    private:
        void drawIdx(DisplayCore *dev, int16_t x, int16_t y, int32_t trans);
        void draw565(DisplayCore *dev, int16_t x, int16_t y, int32_t trans);
        void drawRGB(DisplayCore *dev, int16_t x, int16_t y, int32_t trans);
        void drawRGBA(DisplayCore *dev, int16_t x, int16_t y, int32_t trans);

    public:
        BMP(const char *data);
        void draw(DisplayCore *dev, int16_t x, int16_t y);
        void draw(DisplayCore *dev, int16_t x, int16_t y, uint16_t t);
        void drawTransformed(DisplayCore *dev, int16_t x, int16_t y, uint8_t transform);
        void drawTransformed(DisplayCore *dev, int16_t x, int16_t y, uint8_t transform, uint16_t t);
};

#endif

