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

/*  Bezier Curve Demonstration
 *  
 *  This demo draws a bezier curve and makes it bounce around the screen.
 */

#include <Picadillo.h>
Picadillo tft;

void setup() {
    tft.initializeDevice();
    tft.setBacklight(255);
    tft.fillScreen(Color::Black);
}

void loop() {

    // First generate an initial set of coordinates
    static int x0 = rand() % 320;
    static int x1 = rand() % 320;
    static int x2 = rand() % 320;
    static int x3 = rand() % 320;

    static int y0 = rand() % 480;
    static int y1 = rand() % 480;
    static int y2 = rand() % 480;
    static int y3 = rand() % 480;

    static int dx0 = (rand() & 1) ? 1 : -1;
    static int dx1 = (rand() & 1) ? 1 : -1;
    static int dx2 = (rand() & 1) ? 1 : -1;
    static int dx3 = (rand() & 1) ? 1 : -1;

    static int dy0 = (rand() & 1) ? 1 : -1;
    static int dy1 = (rand() & 1) ? 1 : -1;
    static int dy2 = (rand() & 1) ? 1 : -1;
    static int dy3 = (rand() & 1) ? 1 : -1;

    // Clear the screen
    tft.fillScreen(Color::Black);

    // We'll draw the control points and connecting lines
    // so you can see what is going on.
    tft.drawRectangle(x0 - 1, y0 - 1, 3, 3, Color::Green);
    tft.drawRectangle(x1 - 1, y1 - 1, 3, 3, Color::Green);
    tft.drawRectangle(x2 - 1, y2 - 1, 3, 3, Color::Green);
    tft.drawRectangle(x3 - 1, y3 - 1, 3, 3, Color::Green);
    tft.drawLine(x0, y0, x1, y1, Color::Blue);
    tft.drawLine(x1, y1, x2, y2, Color::Blue);
    tft.drawLine(x2, y2, x3, y3, Color::Blue);

    // The bezier curve has four control points. The first
    // and last are the start and end of the line. The two
    // in the middle are the ones that bend the line into
    // a curve.  The 9th parameter (50 here) is the number of
    // points to render on the line.  The higher the number the
    // slower the drawing, but the smoother the line.
    tft.drawBezier(
        x0, y0,
        x1, y1,
        x2, y2,
        x3, y3,
        50,
        Color::Red);


    // From here down is all about making the line bounce around
    // the screen.
    x0 += dx0;
    x1 += dx1;
    x2 += dx2;
    x3 += dx3;

    y0 += dy0;
    y1 += dy1;
    y2 += dy2;
    y3 += dy3;

    if (x0 == 0 || x0 == 319) dx0 = -dx0;
    if (x1 == 0 || x1 == 319) dx1 = -dx1;
    if (x2 == 0 || x2 == 319) dx2 = -dx2;
    if (x3 == 0 || x3 == 319) dx3 = -dx3;

    if (y0 == 0 || y0 == 479) dy0 = -dy0;
    if (y1 == 0 || y1 == 479) dy1 = -dy1;
    if (y2 == 0 || y2 == 479) dy2 = -dy2;
    if (y3 == 0 || y3 == 479) dy3 = -dy3;

    delay(50);
}
