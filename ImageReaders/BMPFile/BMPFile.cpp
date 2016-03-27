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

#include <BMPFile.h>

void BMPFile::loadImageHeader() {
    _file->seek(0);
    if (_file->read((void *)&_header, sizeof(struct BitmapFileHeader)) != sizeof(struct BitmapFileHeader)) {
        _width = 0;
        _height = 0;
        return;
    }

    if (_file->read((void *)&_info, sizeof(struct BitmapInfoHeader)) != sizeof(struct BitmapInfoHeader)) {
        _width = 0;
        _height = 0;
        return;
    }

    if (_info.biBitCount < 16) {
        _file->seek(sizeof(struct BitmapFileHeader) + _info.biSize);
        int _paletteSize = _info.biClrUsed;
        if (_paletteSize == 0) {
            _paletteSize = 1<<_info.biBitCount;
        }

        for (int i = 0; i < _paletteSize; i++) {
            _file->read((void *)&_palette[i], sizeof(struct BitmapPixel32));
        }
    }
    
    _file->seek(_header.bfBitmapOffset);
    _spos = _header.bfBitmapOffset;

    _width = _info.biWidth;
    _height = _info.biHeight;

    switch (_info.biBitCount) {
        case 8:
            _chunkSize = _width;
            break;
        case 16:
            _chunkSize = _width * 2;
            break;
        case 24:
            _chunkSize = _width * 3;
            break;
        case 32:
            _chunkSize = _width * 4;
    }

    // Round up to 32-bit boundary
    _chunkSize = (_chunkSize + 3) & (~3);
}

void BMPFile::getScanLine(int line, uint8_t *data) {
    uint32_t eof = _header.bfBitmapOffset + (getHeight() * _chunkSize);
    uint32_t pos = eof - ((line + 1) * _chunkSize);
    if (_spos != pos) {
        _file->seek(pos);
    }
    _file->read(data, _chunkSize);
    _spos += _chunkSize;
}

void BMPFile::drawIdx(DisplayCore *dev, int x, int y, int32_t trans) {
    uint8_t data[_chunkSize];
    if (trans < 0) {
        dev->openWindow(x, y, getWidth(), getHeight());
    }
    for (int32_t iy = 0; iy < getHeight(); iy++) {
        getScanLine(iy, data);
        for (uint32_t ix = 0; ix < getWidth(); ix++) {
            struct BitmapPixel32 *p = &_palette[data[ix]];
            color_t col = rgb(p->g, p->b, p->a);
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

void BMPFile::draw565(DisplayCore *dev, int x, int y, int32_t trans) {
    uint8_t data[_chunkSize];
    if (trans < 0) {
        dev->openWindow(x, y, getWidth(), getHeight());
    }
    for (int32_t iy = 0; iy < getHeight(); iy++) {
        getScanLine(iy, data);
        for (uint32_t ix = 0; ix < getWidth(); ix++) {
            uint32_t offset = ix * 2;
            color_t *p = (color_t *)(data + offset);
            if (trans < 0) {
                dev->windowData(*p);
            } else {
                if (*p != trans) {
                    dev->setPixel(x + ix, y + iy, *p);
                }
            }
        }
    }
    if (trans < 0) {
        dev->closeWindow();
    }
}

void BMPFile::drawRGB(DisplayCore *dev, int x, int y, int32_t trans) {
    uint8_t data[_chunkSize];
    if (trans < 0) {
        dev->openWindow(x, y, getWidth(), getHeight());
    }
    for (int32_t iy = 0; iy < getHeight(); iy++) {
        getScanLine(iy, data);
        for (uint32_t ix = 0; ix < getWidth(); ix++) {
            uint32_t offset = ix * 3;
            struct BitmapPixel24 *p = (struct BitmapPixel24 *)(data + offset);
            color_t col = rgb(p->r, p->g, p->b);
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

void BMPFile::drawRGBA(DisplayCore *dev, int x, int y, int32_t trans) {
    uint8_t data[_chunkSize];
    int rShift = 0;
    int gShift = 8;
    int bShift = 16;
    int aShift = 24;
    uint32_t rMask = 0x000000FF;
    uint32_t gMask = 0x0000FF00;
    uint32_t bMask = 0x00FF0000;
    uint32_t aMask = 0xFF000000;
    if (_info.biCompression==3) {
        uint32_t t = _info.biMaskRed;
        rMask = _info.biMaskRed;
        rShift = 0;
        gShift = 0;
        bShift = 0;
        aShift = 0;
        while ((t & 1) == 0) {
            t >>= 1;
            rShift++;
        }
        t = _info.biMaskGreen;
        gMask = _info.biMaskGreen;
        while ((t & 1) == 0) {
            t >>= 1;
            gShift++;
        }
        t = _info.biMaskBlue;
        bMask = _info.biMaskBlue;
        while ((t & 1) == 0) {
            t >>= 1;
            bShift++;
        }
        t = _info.biMaskAlpha;
        aMask = _info.biMaskAlpha;
        while ((t & 1) == 0) {
            t >>= 1;
            aShift++;
        }
    }
    
    for (int32_t iy = 0; iy < getHeight(); iy++) {
        getScanLine(iy, data);
        for (uint32_t ix = 0; ix < getWidth(); ix++) {
            uint32_t offset = ix * 4;
            uint32_t red, green, blue, alpha;
            struct BitmapPixel32 *p = (struct BitmapPixel32 *)(data + offset);
            red = ((p->value & rMask) >> rShift);
            green = ((p->value & gMask) >> gShift);
            blue = ((p->value & bMask) >> bShift);
            alpha = ((p->value & aMask) >> aShift);
            color_t fg = rgb(red, green, blue);
            color_t bg;
            if (trans < 0) {
                bg = dev->colorAt(x + ix, y + iy);
            } else {
                bg = trans;
            }

            if (alpha == 255) {
                dev->setPixel(x + ix, y + iy, fg);
            } else if(alpha > 0) {
                dev->setPixel(x + ix, y + iy, dev->mix(bg, fg, alpha));
            }
        }
    }
}



void BMPFile::draw(DisplayCore *dev, int x, int y) {
    loadImageHeader();
    switch (_info.biBitCount) {
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
    dev->openWindow(x, y, getWidth(), getHeight());
    for (uint32_t iy = 0; iy < getHeight(); iy++) {
        for (uint32_t ix = 0; ix < getWidth(); ix++) {
            dev->windowData(rand());
        }
    }
    dev->closeWindow();
}

void BMPFile::draw(DisplayCore *dev, int x, int y, color_t trans) {
    loadImageHeader();
    switch (_info.biBitCount) {
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
    dev->openWindow(x, y, getWidth(), getHeight());
    for (uint32_t iy = 0; iy < getHeight(); iy++) {
        for (uint32_t ix = 0; ix < getWidth(); ix++) {
            dev->windowData(rand());
        }
    }
    dev->closeWindow();
}

void BMPFile::drawTransformed(DisplayCore *dev, int x, int y, int transform) {}
void BMPFile::drawTransformed(DisplayCore *dev, int x, int y, int transform, color_t t) {}

int BMPFile::getWidth() {
    if (_width == 0) {
        loadImageHeader();
    }
    return _width;
}

int BMPFile::getHeight() {
    if (_height == 0) {
        loadImageHeader();
    }
    return _height;
}


