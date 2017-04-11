#include <DSPI.h>
#include <ILI9341.h>
// DSPI channel 0 is where the screen is connected
DSPI0 spi;

// It is wired to use CS pin 10 and RS (AKA DC) pin 9.
//ILI9341_DSPI tft(spi, 10, 9);
// on HelvePicLCD, CS is 2, RS is 15
ILI9341_DSPI tft(spi, 2, 15);

int tw, th, fh, fs; // (tft width, height and font height and font spacing
int dw, dh, dx, dy; // coordinates of drawing window


// variables needed for 3d cube
double vectors[8][3] = {{1, 1, 1}, { -1, 1, 1}, { -1, -1, 1}, {1, -1, 1}, {1, 1, -1}, { -1, 1, -1}, { -1, -1, -1}, {1, -1, -1}};
int newCorner[8][2];
int oldCorner[8][2];
double perspective = 100.0f;
int deltaX, deltaY, deltaZ;

//----------------- setup
void setup() {
	// If RESET is wired to the MCU's RESET you want a delay here.
	//delay(1000);
	randomSeed(analogRead(A0));
	// if Backlight is connected to A0.
	//pinMode(A0, OUTPUT);
	//digitalWrite(A0, HIGH);
	tft.initializeDevice();
	// You might want to turn this down a little depending
	// on the quality of your wiring.
	spi.setSpeed(20000000UL);
	tft.setRotation(1);
	tw = tft.getWidth();
	th = tft.getHeight();
	fh = tft.stringHeight("A");
	fs = 1;
	dw = tw - 2;
	dh = th - 2 * fh - 8 * fs - 2;
	dx = 1;
	dy = fh + 2 * fs + 3;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			vectors[i][j] = vectors[i][j] * th / 6;
		}
	}
}

//----------------- loop
void loop() {
	int xd;
	int xtics, ytics;
	int val = 0;
	bool redraw = true;
	int arc1 = 0;
	int arc2 = 0;
	// Draw Intro Screen
	xtics = tw / 20 - 1;
	ytics = dh / 20;
	tft.fillScreen(Color::Black);
	tft.fillRectangle(0,         0, tw, fh + 2 * fs, Color::White); // top label frame
	tft.fillRectangle(0, th - fh - 2 * fs, tw, fh + 2 * fs, Color::White); // bottom label frame
	tft.drawRectangle(0,      dy - 1, tw,    dh + 2, Color::Yellow); // center frame
	tft.setTextColor(Color::Black, Color::White);
	tft.setCursor(1,   1);
	tft.print("DisplayCore Demo 1.0 - Welcome");
	xd = (tft.getWidth() - tft.stringWidth("(c) 2017 Dr. Mathias Wilhelm")) / 2;
	tft.setCursor(xd, th - fh - fs);
	tft.print("(c) 2017 Dr. Mathias Wilhelm");
	tft.setTextColor(Color::White, Color::Black);
	xd = (tft.getWidth() - tft.stringWidth("DisplayCore Demo")) / 2;
	tft.setCursor(xd + 1, th / 2);
	tft.print("DisplayCore Demo");
	tft.drawLine(xd - 20, th / 2     , xd - 2, th / 2     , Color::White);
	tft.drawLine(xd - 30, th / 2 + fh / 2, xd - 2, th / 2 + fh / 2, Color::White);
	tft.drawLine(xd - 40, th / 2 + fh  , xd - 2, th / 2 + fh  , Color::White);
	tft.drawLine(tw - xd + 1, th / 2     , tw - xd + 40, th / 2     , Color::White);
	tft.drawLine(tw - xd + 1, th / 2 + fh / 2, tw - xd + 30, th / 2 + fh / 2, Color::White);
	tft.drawLine(tw - xd + 1, th / 2 + fh  , tw - xd + 20, th / 2 + fh  , Color::White);
	tft.setTextColor(Color::Blue, Color::Black);
	xd = (tft.getWidth() - tft.stringWidth("Version 1.0")) / 2;
	tft.setCursor(xd, th / 2 + fh + 2);
	tft.print("Version 1.0");

	for (int i = 15; i < 224; i += 5) {
		tft.drawLine(1, i, (i * 1.44) - 10, 224, Color::Red);
	}

	for (int i = 224; i > 15; i -= 5) {
		tft.drawLine(318, i, (i * 1.44) - 11, 15, Color::Red);
	}

	for (int i = 224; i > 15; i -= 5) {
		tft.drawLine(1, i, 331 - (i * 1.44), 15, Color::Yellow);
	}

	for (int i = 15; i < 224; i += 5) {
		tft.drawLine(318, i, 330 - (i * 1.44), 224, Color::Yellow);
	}

	delay(2000);
	// Draw Trigonomic Functions Screen
	tft.fillScreen(Color::Black);
	tft.fillRectangle(0,         0, tw, fh + 2 * fs, Color::White); // top label frame
	tft.fillRectangle(0, th - fh - 2 * fs, tw, fh + 2 * fs, Color::White); // bottom label frame
	tft.drawRectangle(0,      dy - 1, tw,    dh + 2, Color::Yellow); // center frame
	tft.setTextColor(Color::Black, Color::White);
	tft.setCursor(1,   1);
	tft.print("DisplayCore Demo 1.0 - draw curves");
	xd = (tft.getWidth() - tft.stringWidth("(c) 2017 Dr. Mathias Wilhelm")) / 2;
	tft.setCursor(xd, th - fh - fs);
	tft.print("(c) 2017 Dr. Mathias Wilhelm");
	tft.drawLine(1, th / 2, tw - 2, th / 2, Color::Blue); // draw x-axis
	tft.drawLine(tw / 2, dy + 1, tw / 2, dy + dh - 2, Color::Blue); // draw y-axis

	for (int i = (tw / 2 - 10 * xtics); i < tw - 2; i += 10) {
		tft.drawLine(i, th / 2 - 2, i, th / 2 + 2, Color::Blue);    // draw x tics
	}

	for (int i = (th / 2 - ytics * 10); i < (dy + dh - 2); i += 10) {
		tft.drawLine(tw / 2 - 2, i, tw / 2 + 2, i, Color::Blue);    // draw y tics
	}

	tft.setTextColor(Color::Yellow, Color::Black);
	tft.setCursor(5,  15);
	tft.print("sin(x)");

	for (int i = 1; i < 318; i++) {
		tft.setPixel(i, th / 2 + (sin(((i * 1.13) * 3.14) / 180) * 95), Color::Yellow);
	}

	tft.setTextColor(Color::Red, Color::Black);
	tft.setCursor(5,  15 + fh + 1);
	tft.print("cos(x)");

	for (int i = 1; i < 318; i++) {
		tft.setPixel(i, th / 2 + (cos(((i * 1.13) * 3.14) / 180) * 95), Color::Red);
	}

	tft.setTextColor(Color::White, Color::Black);
	tft.setCursor(5,  15 + 2 * fh + 2);
	tft.print("tan(x)");

	for (int i = 1; i < 318; i++) {
		tft.setPixel(i, th / 2 + (tan(((i * 1.13) * 3.14) / 180)), Color::White);
	}

	delay(2000);
	// Draw Random Data Screen
	tft.fillRectangle(0,         0, tw, fh + 2 * fs, Color::White); // top label frame
	tft.setTextColor(Color::Black, Color::White);
	tft.setCursor(1,   1);
	tft.print("DisplayCore Demo 1.0 - draw data");
	tft.fillRectangle(1, dy + 1, tw - 2, dh - 2, Color::Black);
	tft.setTextColor(Color::White, Color::Black);

	for (int i = 0; i < 20; i++) {
		arc1 = drawValueArc(arc1, random(1023), 1023, 60,  70, 50, Color::Yellow, Color::Black, Color::Blue, redraw);
		arc2 = drawValueArc(arc2,            i,   20, 60, 170, 50, Color::Yellow, Color::Black, Color::Blue, redraw);
		drawValueBar(random(1023), 1023, tw / 2 + 20, 50, 100, 12, Color::Green, Color::Black, redraw);
		drawValueBar(random(1023), 1023, tw / 2 + 20, 70, 100, 12, Color::Red, Color::Black, redraw);
		drawValueBar(i,   30, tw / 2 + 20, 150, 100, 12, Color::Yellow, Color::Black, redraw);
		drawValueBar(30 - i,   30, tw / 2 + 20, 170, 100, 12, Color::Blue, Color::Black, redraw);
		delay(50);
		redraw = false;
	}

	for (int i = 0; i < 20; i++) {
		arc1 = drawValueArc(arc1, random(1023), 1023, 60,  70, 50, Color::Yellow, Color::Black, Color::Blue, redraw);
		arc2 = drawValueArc(arc2,         20 - i,   20, 60, 170, 50, Color::Yellow, Color::Black, Color::Blue, redraw);
		drawValueBar(random(1023), 1023, tw / 2 + 20, 50, 100, 12, Color::Green, Color::Black, redraw);
		drawValueBar(random(1023), 1023, tw / 2 + 20, 70, 100, 12, Color::Red, Color::Black, redraw);
		drawValueBar(i,   30, tw / 2 + 20, 150, 100, 12, Color::Yellow, Color::Black, redraw);
		drawValueBar(30 - i,   30, tw / 2 + 20, 170, 100, 12, Color::Blue, Color::Black, redraw);
		delay(50);
		redraw = false;
	}

	delay(2000);
	// Draw 3d-Cube Screen
	tft.fillRectangle(0,         0, tw, fh + 2 * fs, Color::White); // top label frame
	tft.setTextColor(Color::Black, Color::White);
	tft.setCursor(1,   1);
	tft.print("DisplayCore Demo 1.0 - 3D cube");
	tft.fillRectangle(1, dy + 1, tw - 2, dh - 2, Color::Black);
	tft.setTextColor(Color::White, Color::Black);
	deltaX = random(5) - 3;
	deltaY = random(5) - 3;
	deltaZ = random(5) - 3;

	for (int i = 0; i < 100; i++) {
		rotateX(deltaX);
		rotateY(deltaY);
		rotateZ(deltaZ);
		calculateXY();
		drawVectors(Color::White, Color::Black);
	}

	delay(2000);
}

//-------------- internal routines
int translateX(double x, double z) {
	return (int)((x + tw / 2) + (z * (x / perspective)));
}

int translateY(double y, double z) {
	return (int)((y + th / 2) + (z * (y / perspective)));
}

void rotateX(int angle) {
	double rad, cosa, sina, Yn, Zn;
	rad = angle * PI / 180;
	cosa = cos(rad);
	sina = sin(rad);

	for (int i = 0; i < 8; i++) {
		Yn = (vectors[i][1] * cosa) - (vectors[i][2] * sina);
		Zn = (vectors[i][1] * sina) + (vectors[i][2] * cosa);
		vectors[i][1] = Yn;
		vectors[i][2] = Zn;
	}
}

void rotateY(int angle) {
	double rad, cosa, sina, Xn, Zn;
	rad = angle * PI / 180;
	cosa = cos(rad);
	sina = sin(rad);

	for (int i = 0; i < 8; i++) {
		Xn = (vectors[i][0] * cosa) - (vectors[i][2] * sina);
		Zn = (vectors[i][0] * sina) + (vectors[i][2] * cosa);
		vectors[i][0] = Xn;
		vectors[i][2] = Zn;
	}
}

void rotateZ(int angle) {
	double rad, cosa, sina, Xn, Yn;
	rad = angle * PI / 180;
	cosa = cos(rad);
	sina = sin(rad);

	for (int i = 0; i < 8; i++) {
		Xn = (vectors[i][0] * cosa) - (vectors[i][1] * sina);
		Yn = (vectors[i][0] * sina) + (vectors[i][1] * cosa);
		vectors[i][0] = Xn;
		vectors[i][1] = Yn;
	}
}

void calculateXY() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 2; j++) {
			oldCorner[i][j] = newCorner[i][j];
		}
	}

	newCorner[0][0] = translateX(vectors[0][0], vectors[0][2]); // a1x
	newCorner[0][1] = translateY(vectors[0][1], vectors[0][2]); // a1y
	newCorner[1][0] = translateX(vectors[1][0], vectors[1][2]); // a2x
	newCorner[1][1] = translateY(vectors[1][1], vectors[1][2]); // a2y
	newCorner[2][0] = translateX(vectors[2][0], vectors[2][2]); // a3x
	newCorner[2][1] = translateY(vectors[2][1], vectors[2][2]); // a3y
	newCorner[3][0] = translateX(vectors[3][0], vectors[3][2]); // a4x
	newCorner[3][1] = translateY(vectors[3][1], vectors[3][2]); // a4y
	newCorner[4][0] = translateX(vectors[4][0], vectors[4][2]);
	newCorner[4][1] = translateY(vectors[4][1], vectors[4][2]);
	newCorner[5][0] = translateX(vectors[5][0], vectors[5][2]);
	newCorner[5][1] = translateY(vectors[5][1], vectors[5][2]);
	newCorner[6][0] = translateX(vectors[6][0], vectors[6][2]);
	newCorner[6][1] = translateY(vectors[6][1], vectors[6][2]);
	newCorner[7][0] = translateX(vectors[7][0], vectors[7][2]);
	newCorner[7][1] = translateY(vectors[7][1], vectors[7][2]);
}
void drawVectors(color_t fc, color_t bc) {
	tft.drawLine(oldCorner[0][0], oldCorner[0][1], oldCorner[1][0], oldCorner[1][1], bc);  // a1-a2
	tft.drawLine(newCorner[0][0], newCorner[0][1], newCorner[1][0], newCorner[1][1], fc);
	tft.drawLine(oldCorner[1][0], oldCorner[1][1], oldCorner[2][0], oldCorner[2][1], bc);  // a2-a3
	tft.drawLine(newCorner[1][0], newCorner[1][1], newCorner[2][0], newCorner[2][1], fc);
	tft.drawLine(oldCorner[2][0], oldCorner[2][1], oldCorner[3][0], oldCorner[3][1], bc);  // a3-a4
	tft.drawLine(newCorner[2][0], newCorner[2][1], newCorner[3][0], newCorner[3][1], fc);
	tft.drawLine(oldCorner[3][0], oldCorner[3][1], oldCorner[0][0], oldCorner[0][1], bc);  // a4-a1
	tft.drawLine(newCorner[3][0], newCorner[3][1], newCorner[0][0], newCorner[0][1], fc);
	tft.drawLine(oldCorner[4][0], oldCorner[4][1], oldCorner[5][0], oldCorner[5][1], bc);  // b1-b2
	tft.drawLine(newCorner[4][0], newCorner[4][1], newCorner[5][0], newCorner[5][1], fc);
	tft.drawLine(oldCorner[5][0], oldCorner[5][1], oldCorner[6][0], oldCorner[6][1], bc);  // b2-b3
	tft.drawLine(newCorner[5][0], newCorner[5][1], newCorner[6][0], newCorner[6][1], fc);
	tft.drawLine(oldCorner[6][0], oldCorner[6][1], oldCorner[7][0], oldCorner[7][1], bc);  // b3-b4
	tft.drawLine(newCorner[6][0], newCorner[6][1], newCorner[7][0], newCorner[7][1], fc);
	tft.drawLine(oldCorner[7][0], oldCorner[7][1], oldCorner[4][0], oldCorner[4][1], bc);  // b4-b1
	tft.drawLine(newCorner[7][0], newCorner[7][1], newCorner[4][0], newCorner[4][1], fc);
	tft.drawLine(oldCorner[0][0], oldCorner[0][1], oldCorner[4][0], oldCorner[4][1], bc);  // a1-b1
	tft.drawLine(newCorner[0][0], newCorner[0][1], newCorner[4][0], newCorner[4][1], fc);
	tft.drawLine(oldCorner[1][0], oldCorner[1][1], oldCorner[5][0], oldCorner[5][1], bc);  // a2-b2
	tft.drawLine(newCorner[1][0], newCorner[1][1], newCorner[5][0], newCorner[5][1], fc);
	tft.drawLine(oldCorner[2][0], oldCorner[2][1], oldCorner[6][0], oldCorner[6][1], bc);  // a3-b3
	tft.drawLine(newCorner[2][0], newCorner[2][1], newCorner[6][0], newCorner[6][1], fc);
	tft.drawLine(oldCorner[3][0], oldCorner[3][1], oldCorner[7][0], oldCorner[7][1], bc);  // a4-b4
	tft.drawLine(newCorner[3][0], newCorner[3][1], newCorner[7][0], newCorner[7][1], fc);
}

int drawValueArc(int old, int val, int vmx, int x, int y, int r, color_t fc, color_t bc, color_t cc, bool refresh) {
	char sd[5];
	int d = val;
	sprintf(sd, "%4d", val);
	tft.setCursor(x - tft.stringWidth(sd) / 2, y - 2);
	tft.print(sd);
	val = map(val, 0, vmx, 0, 359);
	old = map(old, 0, vmx, 0, 359);

	if (refresh) { // refresh the borders if requested (not every time the value gets updated)
		drawArc(x, y,    r, 0, 359, cc);
		drawArc(x, y, r - 10, 0, 359, cc);
	}

	if (val > old) {
		drawArc(x, y,  r - 5, old, val, fc);
	}

	if (val < old) {
		drawArc(x, y,  r - 5, val, old, bc);
	}

	return d;
}

void drawValueBar(int val, int vmx, int x, int y, int w, int h, color_t fc, color_t bc, bool refresh) {
	char sd[5];
	sprintf(sd, "%4d", val);
	tft.setCursor(x - tft.stringWidth(sd) - 4, y + 2);
	tft.print(sd);
	val = map(val, 0, vmx, 0, w - 4);

	if (refresh) {
		tft.drawRectangle(x,       y,       w,   h, fc);
		tft.fillRectangle(x + 2,     y + 2,     w - 4, h - 4, bc);
	}

	tft.fillRectangle(x + 2    , y + 2,     val, h - 4, fc);
	tft.fillRectangle(x + 3 + val, y + 2, w - val - 5, h - 4, bc);
}

void drawArc(int x, int y, int r, int startAngle, int endAngle, color_t color) {
	/* original code from Henning Karlsen (http://www.rinkydinkelectronics.com)
	  This library is free software; you can redistribute it and/or
	  modify it under the terms of the CC BY-NC-SA 3.0 license.
	  Please see the included documents for further information.
	*/
	int cx, cy;
	startAngle -= 90;
	endAngle   -= 90;

	if (startAngle != endAngle) {
		for (int d = startAngle + 1; d < endAngle + 1; d++) {
			cx = x + cos((d * 3.14) / 180) * r;
			cy = y + sin((d * 3.14) / 180) * r;
			tft.setPixel(cx, cy, color);
		}
	} else {
		cx = x + cos((startAngle * 3.14) / 180) * r;
		cy = y + sin((startAngle * 3.14) / 180) * r;
		tft.setPixel(cx, cy, color);
	}
}
