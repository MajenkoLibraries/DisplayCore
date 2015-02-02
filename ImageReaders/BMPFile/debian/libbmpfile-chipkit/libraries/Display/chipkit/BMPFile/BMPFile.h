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

#ifndef _BMPFILE_H
#define _BMPFILE_H

#include <DSPI.h>
#include <TFT.h>
#include <SD.h>

class BMPFile : public Image {
    public: // should be private
        struct BitmapFileHeader _header;
        struct BitmapInfoHeader _info;
        File *_file;
        struct BitmapPixel32 _palette[256];
        uint16_t _paletteSize;
        uint32_t _chunkSize;
        uint32_t _spos;

    private:
        void getScanLine(int16_t, uint8_t*);
        void drawIdx(TFT *dev, int16_t x, int16_t y, int32_t trans);
        void draw565(TFT *dev, int16_t x, int16_t y, int32_t trans);
        void drawRGB(TFT *dev, int16_t x, int16_t y, int32_t trans);
        void drawRGBA(TFT *dev, int16_t x, int16_t y, int32_t trans);

    public:
        BMPFile(File &file) : _file(&file) { _width = 0; _height = 0; };
        void draw(TFT *dev, int16_t x, int16_t y);
        void draw(TFT *dev, int16_t x, int16_t y, uint16_t t);
        void drawTransformed(TFT *dev, int16_t x, int16_t y, uint8_t transform);
        void drawTransformed(TFT *dev, int16_t x, int16_t y, uint8_t transform, uint16_t t);

        virtual uint16_t getWidth();
        virtual uint16_t getHeight();

    private:
        void loadImageHeader();

};

#endif

