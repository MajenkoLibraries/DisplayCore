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
 * Screen: PICadillo-35t
 * 
 * Display some scary looking kitten faces on the screen.  The kitten image is
 * BMP format ABGR, so it has alpha blending to allow the images to overlay
 * each other cleanly.
 * 
 * NOTE: Requires UECIDE to convert and link the binary data. If you don't have UECIDE,
 * get it from http://www.uecide.org
 */

#include <Picadillo.h>
#include <BMP.h>
#include <Topaz.h>

extern char kitten1_data[] asm("_binary_objects_kitten1_bmp_start");

BMP kitten1(kitten1_data);

// Set up the screen to use
Picadillo tft;

void setup() {
	tft.initializeDevice();
    tft.setBacklight(255);
	tft.setRotation(0);
	tft.setFont(Fonts::Topaz);
	tft.setTextColor(Color::White);
	tft.fillScreen(Color::Pink);
}

void loop()
{
	int x = (rand() % (tft.getWidth() + (kitten1.getWidth() * 2))) - kitten1.getWidth();
	int y = (rand() % (tft.getHeight() + (kitten1.getHeight() * 2))) - kitten1.getHeight();
	kitten1.draw(&tft, x, y);
}
