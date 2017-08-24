#include <Topaz.h>
#include <PG25664CG.h>

// Select one of these options:

/* Slow, but flexible. You can use any pins on the board, but
 * as a result it's quite long winded to manipulate the pins.
 * 
 * Pin list is board pin numbers in the sequence:
 * DC, WR, RD, CS, RESET, D0, D1, D2, D3, D4, D5, D6, D7
 */
// PG25664CG tft(A0, A1, A2, A3, A4, A8, A9, A10, A11, A12, A13, A14, A15);

/* For fast operation use an entire 16-bit port (PORT B) and
 * do direct port manipulation.  The pin numbers are the bit
 * position within PORT B, not the pin numbers on the board.
 * The last number is the starting bit offset for 8 consecutive
 * bits for the data value.
 *
 * Pins in this order: DC WR, RD, CS, RESET, DATA
 */
// PG25664CG_PORTB tft(0, 1, 2, 3, 4, 8);

/* The fastest operation possible - Parallel Master Port.
 * You are restricted to a specific set of pins (except reset)
 * but operation is blisteringly fast.
 * 
 * Only parameter specified is the reset pin number since this
 * is not part of the PMP specification.
 */
PG25664CG_PMP tft(9);

int zOff = 150;
int xOff = 0;
int yOff = 0;
int cSize = 50;
int view_plane = 32;
float angleX = 0;
float angleY = 0;
float angleZ = 0;
int hres = 64;
int vres = 64;
unsigned char frame = 0;
unsigned long timer = 0;

float cube3d[8][3] = {
	{xOff - cSize,yOff + cSize,zOff - cSize	},
	{xOff + cSize,yOff + cSize,zOff - cSize	},
	{xOff - cSize,yOff - cSize,zOff - cSize	},
	{xOff + cSize,yOff - cSize,zOff - cSize	},
	{xOff - cSize,yOff + cSize,zOff + cSize	},
	{xOff + cSize,yOff + cSize,zOff + cSize	},
	{xOff - cSize,yOff - cSize,zOff + cSize	},
	{xOff + cSize,yOff - cSize,zOff + cSize	}
};
unsigned int cube2d[8][2];

unsigned int oldCube2d[8][2];

void setup() {
	tft.initializeDevice();
	timer = millis()+1000;
	frame = 0;
	tft.fillScreen(Color::Black);
	tft.setFont(Fonts::Topaz);
	tft.setTextColor(0x08);
}

uint16_t color = Color::White;

void loop() {

	xrotate(angleX);
	yrotate(angleY);
	zrotate(angleZ);
	tft.startBuffer(); 
	printcube();

	angleX = 0.01;//double(analogRead(0))/1024-0.5;
	angleY = 0.02;//double(analogRead(1))/1024-0.5;
	angleZ = 0.005;//double(analogRead(2))/1024-0.5;
	tft.setCursor(100, 10);
	tft.print("X: ");
	tft.print(cube3d[0][0], 6);
	tft.print("   ");

	tft.setCursor(100, 30);
	tft.print("Y: ");
	tft.print(cube3d[0][1], 6);
	tft.print("   ");

	tft.setCursor(100, 50);
	tft.print("Z: ");
	tft.print(cube3d[0][2], 6);
	tft.print("   ");
	tft.endBuffer();
}

void printcube() {
	for(byte i = 0; i < 8; i++) {
		cube2d[i][0] = (unsigned int)((cube3d[i][0] * view_plane / cube3d[i][2]) + (hres/2));
		cube2d[i][1] = (unsigned int)((cube3d[i][1] * view_plane / cube3d[i][2]) + (vres/2));
	}

//	draw_cube(cube2d, color);
	draw_cube(oldCube2d, Color::Black);
	draw_cube(cube2d, color);

	for (byte i = 0; i < 8; i++) {
		oldCube2d[i][0] = cube2d[i][0];
		oldCube2d[i][1] = cube2d[i][1];
	}
}

void zrotate(float q) {
	float tx,ty,temp;
	for(byte i = 0; i < 8; i++) {
		tx = cube3d[i][0] - xOff;
		ty = cube3d[i][1] - yOff;
		temp = tx * cos(q) - ty * sin(q);
		ty = tx * sin(q) + ty * cos(q);
		tx = temp;
		cube3d[i][0] = tx + xOff;
		cube3d[i][1] = ty + yOff;
	}
}

void yrotate(float q) {
	float tx,tz,temp;
	for(byte i = 0; i < 8; i++) {
		tx = cube3d[i][0] - xOff;
		tz = cube3d[i][2] - zOff;
		temp = tz * cos(q) - tx * sin(q);
		tx = tz * sin(q) + tx * cos(q);
		tz = temp;
		cube3d[i][0] = tx + xOff;
		cube3d[i][2] = tz + zOff;
	}
}

void xrotate(float q) {
	float ty,tz,temp;
	for(byte i = 0; i < 8; i++) {
		ty = cube3d[i][1] - yOff;
		tz = cube3d[i][2] - zOff;
		temp = ty * cos(q) - tz * sin(q);
		tz = ty * sin(q) + tz * cos(q);
		ty = temp;
		cube3d[i][1] = ty + yOff;
		cube3d[i][2] = tz + zOff;
	}
}

void draw_cube(unsigned int c2d[8][2], uint16_t col) {
	static unsigned int fps;
	char buf[30];
	tft.drawLine(c2d[0][0],c2d[0][1],c2d[1][0],c2d[1][1], col);
	tft.drawLine(c2d[0][0],c2d[0][1],c2d[2][0],c2d[2][1], col);
	tft.drawLine(c2d[0][0],c2d[0][1],c2d[4][0],c2d[4][1], col);
	tft.drawLine(c2d[1][0],c2d[1][1],c2d[5][0],c2d[5][1], col);
	tft.drawLine(c2d[1][0],c2d[1][1],c2d[3][0],c2d[3][1], col);
	tft.drawLine(c2d[2][0],c2d[2][1],c2d[6][0],c2d[6][1], col);
	tft.drawLine(c2d[2][0],c2d[2][1],c2d[3][0],c2d[3][1], col);
	tft.drawLine(c2d[4][0],c2d[4][1],c2d[6][0],c2d[6][1], col);
	tft.drawLine(c2d[4][0],c2d[4][1],c2d[5][0],c2d[5][1], col);
	tft.drawLine(c2d[7][0],c2d[7][1],c2d[6][0],c2d[6][1], col);
	tft.drawLine(c2d[7][0],c2d[7][1],c2d[3][0],c2d[3][1], col);
	tft.drawLine(c2d[7][0],c2d[7][1],c2d[5][0],c2d[5][1], col);

	tft.drawLine(c2d[0][0],c2d[0][1],c2d[5][0],c2d[5][1], col);
	tft.drawLine(c2d[1][0],c2d[1][1],c2d[4][0],c2d[4][1], col);
	tft.drawLine(c2d[2][0],c2d[2][1],c2d[7][0],c2d[7][1], col);
	tft.drawLine(c2d[3][0],c2d[3][1],c2d[6][0],c2d[6][1], col);
}
