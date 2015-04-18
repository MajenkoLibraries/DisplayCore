/*
 * Copyright (c) 2015, Majenko Technologies
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

#ifndef _NATIVEFB_H
#define _NATIVEFB_H

#include <DisplayCore.h>

#include <SDL/SDL.h>

class SDL;

class SDLTouch : public Touch {
    public:
        SDLTouch(uint16_t w, uint16_t h) : Touch(w, h) {}
        boolean isPressed();

        uint16_t x();
        uint16_t y();

        void setRotation(uint8_t r) {}
        void sample();

        void initializeDevice() {}
        
    friend SDL;

    private:
        uint16_t _x;
        uint16_t _y;
        boolean _pressed;

        void press(uint16_t x, uint16_t y) { _pressed = true; _x = x; _y = y; }
        void release() { _pressed = false; }
        
        
};

class SDL : public DisplayCore {

    public:
        static const uint8_t Windowed = 0;
        static const uint8_t Window = 0;
        static const uint8_t Fullscreen = 0x01;
        static const uint8_t DoubleBuffer = 0x02;
        static const uint8_t Doublebuffer = 0x02;
        static const uint8_t DoubleBuffered = 0x02;
        static const uint8_t Doublebuffered = 0x02;

        SDL(uint16_t w, uint16_t h, uint8_t t) : DisplayCore(), _width(w), _height(h), _type(t) {}

        void initializeDevice();
        void setPixel(int16_t x, int16_t y, uint16_t c);
        uint16_t colorAt(int16_t x, int16_t y);

        void setRotation(uint8_t r) { }
        void displayOn() { }
        void displayOff() { }
        void invertDisplay(boolean b) { }

        void fillScreen(uint16_t c);
        void fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);


        uint16_t getWidth();
        uint16_t getHeight();

        void startBuffer();
        void endBuffer();

    private:
        uint16_t _width;
        uint16_t _height;
        uint16_t _type;

        SDL_Surface *_display;

        int32_t _buffered;

    friend SDLTouch;
};

#endif
