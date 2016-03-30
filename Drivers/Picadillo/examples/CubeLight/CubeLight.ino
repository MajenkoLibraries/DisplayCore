#include <Picadillo.h>

Picadillo tft;

point3d cubepoints[8] = {
	{ -100,  100, -100 },
	{ 100,  100, -100 },
	{ -100, -100, -100 },
	{ 100, -100, -100 },
	{ -100,  100,  100 },
	{ 100,  100,  100 },
	{ -100, -100,  100 },
	{ 100, -100,  100 }
};

triangle cube[13] = {
	{ cubepoints[0], cubepoints[1], cubepoints[3], Color::Red },
	{ cubepoints[0], cubepoints[3], cubepoints[2], Color::Red },

	{ cubepoints[0], cubepoints[4], cubepoints[6], Color::Green },
	{ cubepoints[0], cubepoints[6], cubepoints[3], Color::Green },

	{ cubepoints[0], cubepoints[1], cubepoints[5], Color::Blue },
	{ cubepoints[0], cubepoints[5], cubepoints[4], Color::Blue },

	{ cubepoints[1], cubepoints[3], cubepoints[7], Color::Yellow },
	{ cubepoints[1], cubepoints[7], cubepoints[5], Color::Yellow },

	{ cubepoints[2], cubepoints[6], cubepoints[7], Color::Magenta },
	{ cubepoints[2], cubepoints[7], cubepoints[3], Color::Magenta },

	{ cubepoints[4], cubepoints[5], cubepoints[7], Color::Cyan },
	{ cubepoints[4], cubepoints[7], cubepoints[6], Color::Cyan },

    // This is a little white triangle off to one side by itself.
    { {150, 150, 150}, {200, 200, 200}, {170, 190, 220}, Color::White },
};

Scene s(cube, sizeof(cube) / sizeof(cube[0]));

point3d cpos;
point3d cang;

void setup() {
	tft.initializeDevice();
	tft.setBacklight(255);
	tft.setRotation(1);
	tft.fillScreen(Color::Red);
    cpos.x = 500;
    cpos.y = 500;
    cpos.z = 1000;
	s.setCameraPosition(cpos);
    s.setLightPosition(200, 400, 700);
    cang.x = -20;
    cang.y = 20;
    cang.z = 0;
	s.setCameraAngle(cang);
    s.setAmbientLight(0.25);
	tft.setFOV(240); // Half the horizontal width is best
}

void loop() {
    cang.y+=2;
    if (cang.y >= 360) cang.y -= 360;
    cang.x++;
    if (cang.x >= 360) cang.x -= 360;

    float beta = cang.x * (PI/180);
    float alpha = cang.y * (PI/180);
    int r = 500;
    cpos.x = r * cos(beta) * sin(alpha);
    cpos.z = r * cos(beta) * cos(alpha);
    cpos.y = -r * sin(beta);
    
    s.setLightPosition(cpos);

    tft.startBuffer();
    tft.fillScreen(Color::Black);
    point3d lpos = s.translatePoint(cpos);
    point2d l2d = tft.map3Dto2D(lpos);

    if (cpos.z < 0) {
        tft.fillCircle(l2d.x, l2d.y, cpos.z / (r/10) + 10, Color::White);
    }    
    s.render(tft);
    if (cpos.z >= 0) {
        tft.fillCircle(l2d.x, l2d.y, cpos.z / (r/10) + 10, Color::White);
    }
	tft.endBuffer();
	delay(100);
}

