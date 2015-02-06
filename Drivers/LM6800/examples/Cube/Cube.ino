#include <Topaz.h>
#include <LM6800.h>

// Pins in this order: D0 - D8, CSA, CSB, CSC, E, RS, RW, RESET
LM6800 tft(70, 71, 72, 73, 74, 75, 76, 77, 81, 82, 83,	80, 78, 79, 84);


int zOff = 150;
int xOff = 0;
int yOff = 0;
int cSize = 50;
int view_plane = LM6800::Height / 2;
float angleX = 0;
float angleY = 0;
float angleZ = 0;
int hres = LM6800::Height;
int vres = LM6800::Height;
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
