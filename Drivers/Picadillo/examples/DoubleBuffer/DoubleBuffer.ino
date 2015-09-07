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

/*
 * This sketch demonstrates how we can use a small in-memory framebuffer to
 * perform double buffering operations. An image is built up in RAM before
 * being displayed to the screen. This avoids any unnecessary flickering as the
 * image is being redrawn.
 * 
 * The background image is best stored in flash as a raw 565 image since that 
 * is by far the fastest format to render.
 */

#include <Picadillo.h>
#include <Liberation.h>
#include <Framebuffer565.h>
#include <Raw565.h>

Picadillo tft;

// We want a small framebuffer for working in. 128x32 pixels, and the fastest
// full colour framebuffer driver.
uint16_t buffer[128 * 32];
Framebuffer565 fb(128, 32, buffer);

// This is the background image we will use. It's fastest to have a 565 image
// stored in flash, but it could just as well be a BMP on an SD card, or another
// small framebuffer with an image drawn into it.
extern uint16_t wall_565[] asm("_binary_objects_wall_565_start");
Raw565 wall(wall_565, 128, 32);

void setup() {
    tft.initializeDevice();
    tft.setBacklight(255);
    tft.setRotation(0);
    tft.fillScreen(Color::Black);

    // We're going to be working in the framebuffer, so set it's font instead
    // of the TFT's font.
    fb.initializeDevice();
    fb.setFont(Fonts::Liberation28);
}

void loop() {

    // First draw the background image into the framebuffer
    wall.draw(fb, 0, 0);

    
    int s = millis();

    // Then place the text over the top.
    fb.setCursor(3, 3);
    fb.setTextColor(Color::Gray10, Color::Gray10);
    fb.print(s);

    fb.setCursor(0, 0);
    fb.setTextColor(Color::Blue, Color::Blue);
    fb.print(s);

    // Finally output the framebuffer to the screen.
    fb.draw(tft, 100, 100);
}

