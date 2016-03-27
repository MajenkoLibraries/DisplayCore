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
        SDLTouch(int w, int h) : Touch(w, h) {}
        boolean isPressed();

        int x();
        int y();
        int rawX() { return x(); }
        int rawY() { return y(); }

        void setRotation(int r) {}
        void sample();

        void initializeDevice() {}
        
    private:
        int _x;
        int _y;
        boolean _pressed;

        void press(int x, int y) { _pressed = true; _x = x; _y = y; }
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

        SDL(int w, int h, uint8_t t) : DisplayCore(), _width(w), _height(h), _type(t) {}
        SDL(uint8_t t) : DisplayCore(), _width(0), _height(0), _type(t) {}

        void initializeDevice();
        void setPixel(int x, int y, color_t c);
        color_t colorAt(int x, int y);

        void setRotation(int r) { }
        void displayOn() { }
        void displayOff() { }
        void invertDisplay(boolean b) { }

        void fillScreen(color_t c);
        void fillRectangle(int x, int y, int w, int h, color_t color);


        int getWidth();
        int getHeight();

        void startBuffer();
        void endBuffer();

        void flip();

        void hideCursor();
        void showCursor();

        void openWindow(int x0, int y0, int x1, int y1);
        void windowData(color_t d);
        void windowData(color_t *d, int l);
        void closeWindow();


    private:
        int _width;
        int _height;
        int _type;

        SDL_Surface *_display;

        int _buffered;
        int _min_x;
        int _min_y;
        int _max_x;
        int _max_y;

        int _winx;
        int _winy;
        int _winw;
        int _winh;

        int _win_px;
        int _win_py;

        SDL_Surface *_blitSfc;
        uint32_t _win_ptr;

        void setBound(int x, int y);

};

#endif
