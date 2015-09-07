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
 * This example demonstrates the use of filter chains for modifying the colour of
 * image data on the fly.  Filter chains are joined together and the colour of a
 * pixel in the image is passedalong the chain from one filter to the next, and the 
 * final filter returns the resultant pixel colour to the drawing routine.  Any number
 * of filters can be chained together, and the chains can be rearranged to achieve
 * different effects.
 */
#include <Picadillo.h>
#include <Filters.h>
#include <Raw565.h>
#include <Arial.h>

Picadillo tft;
AnalogTouch ts(LCD_XL, LCD_XR, LCD_YU, LCD_YD, 320, 480);

extern uint16_t basil_565[] asm("_binary_objects_basil_565_start");

// We now create a selection of raw 565 image wrappers for each image.

Raw565 basil(basil_565, 320, 480);

Monochrome mono;
Contrast cst;
Brightness brt;
Tint tint;
Noise noise(10);

AdjustHSV hsv;

Invert inv;

void setup() {
    ts.initializeDevice();
    ts.scaleX(4.3);
    ts.scaleY(3.3);
    ts.offsetY(5);
    tft.initializeDevice();
    tft.setBacklight(255);
    tft.setRotation(0);
    tft.fillScreen(Color::Black);
    tft.setFont(Fonts::Arial16);
    mono.chain(cst);
        cst.chain(brt);
        brt.chain(tint);

    cst.adjustContrast(+200);
    brt.adjustBrightness(+60);

    hsv.adjustHue(128);
}

void loop() {
    basil.removeFilter();
    basil.draw(&tft, 0, 0);
    message("Tap for monochrome");
    waitForTap();
    
    basil.setFilter(mono);
    mono.endChain();
    basil.draw(&tft, 0, 0);
    message("Tap to change contrast");
    waitForTap();

    mono.chain(cst);
    cst.endChain();
    basil.draw(&tft, 0, 0);
    message("Tap to change brightness");
    waitForTap();

    cst.chain(brt);
    brt.endChain();
    basil.draw(&tft, 0, 0);
    message("Tap to change tint");
    waitForTap();

    brt.chain(tint);
    tint.endChain();
    basil.draw(&tft, 0, 0);
    message("Next: A different order");
    waitForTap();





    basil.removeFilter();
    basil.draw(&tft, 0, 0);
    message("Tap for monochrome");
    waitForTap();
    
    basil.setFilter(mono);
    mono.endChain();
    basil.draw(&tft, 0, 0);
    message("Tap to tint");
    waitForTap();

    mono.chain(tint);
    tint.endChain();
    basil.draw(&tft, 0, 0);
    message("Tap to change brightness");
    waitForTap();

    tint.chain(brt);
    brt.endChain();
    basil.draw(&tft, 0, 0);
    message("Tap to change contrast");
    waitForTap();

    brt.chain(cst);
    cst.endChain();
    basil.draw(&tft, 0, 0);
    message("Now let's add some noise");
    waitForTap();

    cst.chain(noise);
    noise.endChain();
    basil.draw(&tft, 0, 0);
    message("Next: The HSV Filter");
    waitForTap();







    basil.removeFilter();
    basil.draw(&tft, 0, 0);
    message("Tap to change hue");
    waitForTap();

    basil.setFilter(hsv);
    hsv.adjustHue(128);
    hsv.adjustSaturation(0);
    hsv.adjustValue(0);
    basil.draw(&tft, 0, 0);
    message("Tap to change saturation");
    waitForTap();

    hsv.adjustHue(128);
    hsv.adjustSaturation(-100);
    hsv.adjustValue(0);
    basil.draw(&tft, 0, 0);
    message("Tap to change value");
    waitForTap();

    hsv.adjustHue(128);
    hsv.adjustSaturation(-100);
    hsv.adjustValue(100);
    basil.draw(&tft, 0, 0);
    message("Next: inversion");
    waitForTap();



    basil.removeFilter();
    basil.draw(&tft, 0, 0);
    message("Tap to invert");
    waitForTap();

    basil.setFilter(inv);
    inv.endChain();
    basil.draw(&tft, 0, 0);
    message("How's that then?");
    waitForTap();


}

void waitForTap() {
    ts.sample();
    while (!ts.isPressed()) {
        ts.sample();
    }
    delay(50);
    while (ts.isPressed()) {
        ts.sample();
    }
}

void message(char *s) {
    int sw = tft.stringWidth(s);
    tft.setCursor(160 - (sw / 2), 0);
    tft.setTextColor(Color::White, Color::Black);
    tft.print(s);
}

