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

#include <BMP.h>

BMP::BMP(const char *data) {
    _data = data;
    _header = (struct BitmapFileHeader *)_data;
    if (_header->bfType != 0x4D42) {
        return;
    }
    _info = (struct BitmapInfoHeader *)(_data + sizeof(struct BitmapFileHeader));
    _image = _data + _header->bfBitmapOffset;
    _width = _info->biWidth;
    _height = _info->biHeight;

    if (_info->biBitCount < 16) {
        _palette = (struct BitmapPixel32 *)(_data + sizeof(struct BitmapFileHeader) + sizeof(struct BitmapInfoHeader));
        _paletteSize = _info->biClrUsed;
        if (_paletteSize == 0) {
            _paletteSize = 1<<_info->biBitCount;
        }
    }
}

void BMP::drawIdx(DisplayCore *dev, int16_t x, int16_t y, int32_t trans) {
    if (trans < 0) {
        dev->openWindow(x, y, getWidth(), getHeight());
    }
    for (uint32_t iy = 0; iy < getHeight(); iy++) {
        uint32_t line = getHeight() - iy - 1;
        for (uint32_t ix = 0; ix < getWidth(); ix++) {
            uint32_t pix = line * getWidth() + ix;
            struct BitmapPixel32 *p = &_palette[_image[pix]];
            uint16_t col = rgb(p->g, p->b, p->a);
            if (_filter != NULL) {
                col = _filter->process(col);
            }
            if (trans < 0) {
                dev->windowData(col);
            } else {
                if (col != trans) {
                    dev->setPixel(x + ix, y + iy, col);
                }
            }
        }
    }
    if (trans < 0) {
        dev->closeWindow();
    }
}

void BMP::draw565(DisplayCore *dev, int16_t x, int16_t y, int32_t trans) {
    if (trans < 0) {
        dev->openWindow(x, y, getWidth(), getHeight());
    }
    for (uint32_t iy = 0; iy < getHeight(); iy++) {
        uint32_t line = getHeight() - iy - 1;
        for (uint32_t ix = 0; ix < getWidth(); ix++) {
            uint32_t pix = line * getWidth() + ix;
            uint32_t offset = pix * 2;
            uint16_t *p = (uint16_t *)(_image + offset);
            uint16_t col = *p;
            if (_filter != NULL) {
                col = _filter->process(col);
            }
            if (trans < 0) {
                dev->windowData(col);
            } else {
                if (*p != trans) {
                    dev->setPixel(x + ix, y + iy, col);
                }
            }
        }
    }
    if (trans < 0) {
        dev->closeWindow();
    }
}

void BMP::drawRGB(DisplayCore *dev, int16_t x, int16_t y, int32_t trans) {
    if (trans < 0) {
        dev->openWindow(x, y, getWidth(), getHeight());
    }
    for (uint32_t iy = 0; iy < getHeight(); iy++) {
        uint32_t line = getHeight() - iy - 1;
        for (uint32_t ix = 0; ix < getWidth(); ix++) {
            uint32_t pix = line * getWidth() + ix;
            uint32_t offset = pix * 3;
            struct BitmapPixel24 *p = (struct BitmapPixel24 *)(_image + offset);
            uint16_t col = rgb(p->r, p->g, p->b);
            if (_filter != NULL) {
                col = _filter->process(col);
            }
            if (trans < 0) {
                dev->windowData(col);
            } else {
                if (col != trans) {
                    dev->setPixel(x + ix, y + iy, col);
                }
            }
        }
    }
    if (trans < 0) {
        dev->closeWindow();
    }
}

void BMP::drawRGBA(DisplayCore *dev, int16_t x, int16_t y, int32_t trans) {
    int rShift = 0;
    int gShift = 8;
    int bShift = 16;
    int aShift = 24;
    uint32_t rMask = 0x000000FF;
    uint32_t gMask = 0x0000FF00;
    uint32_t bMask = 0x00FF0000;
    uint32_t aMask = 0xFF000000;
    if (_info->biCompression==3) {
        rShift = 0;
        gShift = 0;
        bShift = 0;
        aShift = 0;
        uint32_t t = _info->biMaskRed;
        rMask = _info->biMaskRed;
        while ((t & 1) == 0) {
            t >>= 1;
            rShift++;
        }
        t = _info->biMaskGreen;
        gMask = _info->biMaskGreen;
        while ((t & 1) == 0) {
            t >>= 1;
            gShift++;
        }
        t = _info->biMaskBlue;
        bMask = _info->biMaskBlue;
        while ((t & 1) == 0) {
            t >>= 1;
            bShift++;
        }
        t = _info->biMaskAlpha;
        aMask = _info->biMaskAlpha;
        while ((t & 1) == 0) {
            t >>= 1;
            aShift++;
        }
    } 
    for (uint32_t iy = 0; iy < getHeight(); iy++) {
        uint32_t line = getHeight() - iy - 1;
        for (uint32_t ix = 0; ix < getWidth(); ix++) {
            uint32_t pix = line * getWidth() + ix;
            uint32_t offset = pix * 4;
            uint32_t red, green, blue, alpha;
            struct BitmapPixel32 *p = (struct BitmapPixel32 *)(_image + offset);
            red = ((p->value & rMask) >> rShift);
            green = ((p->value & gMask) >> gShift);
            blue = ((p->value & bMask) >> bShift);
            alpha = ((p->value & aMask) >> aShift);
            int16_t fg = rgb(red, green, blue);
            if (_filter != NULL) {
                fg = _filter->process(fg);
            }

            if (alpha == 255) {
                dev->setPixel(x + ix, y + iy, fg);
            } else if(alpha > 0) {
                int16_t bg;
                if (trans < 0) {
                    bg = dev->colorAt(x + ix, y + iy);
                } else {
                    bg = trans;
                }
                dev->setPixel(x + ix, y + iy, dev->mix(bg, fg, alpha));
            }
        }
    }
}

void BMP::draw(DisplayCore *dev, int16_t x, int16_t y) {
    switch (_info->biBitCount) {
        case 8:
            drawIdx(dev, x, y, -1);
            return;
        case 16:
            draw565(dev, x, y, -1);
            return;
        case 24:
            drawRGB(dev, x, y, -1);
            return;
        case 32:
            drawRGBA(dev, x, y, -1);
            return;
    }
        
    // Unable to decode the image - use colour fuzz instead.
    for (uint32_t iy = 0; iy < getHeight(); iy++) {
        for (uint32_t ix = 0; ix < getWidth(); ix++) {
            dev->setPixel(x + ix, y + iy, rand() & 0xFFFF);
        }
    }
}

void BMP::draw(DisplayCore *dev, int16_t x, int16_t y, uint16_t trans) {
    switch (_info->biBitCount) {
        case 8:
            drawIdx(dev, x, y, trans);
            return;
        case 16:
            draw565(dev, x, y, trans);
            return;
        case 24:
            drawRGB(dev, x, y, trans);
            return;
        case 32:
            drawRGBA(dev, x, y, trans);
            return;
    }
        
    // Unable to decode the image - use colour fuzz instead.
    for (uint32_t iy = 0; iy < getHeight(); iy++) {
        for (uint32_t ix = 0; ix < getWidth(); ix++) {
            dev->setPixel(x + ix, y + iy, rand() & 0xFFFF);
        }
    }
}

void BMP::drawTransformed(DisplayCore *dev, int16_t x, int16_t y, uint8_t transform) {}
void BMP::drawTransformed(DisplayCore *dev, int16_t x, int16_t y, uint8_t transform, uint16_t t) {}

