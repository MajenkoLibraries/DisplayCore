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
	{ cubepoints[0], cubepoints[2], cubepoints[3], Color::Red },

	{ cubepoints[0], cubepoints[4], cubepoints[6], Color::Green },
	{ cubepoints[0], cubepoints[2], cubepoints[6], Color::Green },

	{ cubepoints[0], cubepoints[1], cubepoints[5], Color::Blue },
	{ cubepoints[0], cubepoints[4], cubepoints[5], Color::Blue },

	{ cubepoints[1], cubepoints[3], cubepoints[7], Color::Yellow },
	{ cubepoints[1], cubepoints[5], cubepoints[7], Color::Yellow },

	{ cubepoints[2], cubepoints[6], cubepoints[7], Color::Magenta },
	{ cubepoints[2], cubepoints[3], cubepoints[7], Color::Magenta },

	{ cubepoints[4], cubepoints[5], cubepoints[7], Color::Cyan },
	{ cubepoints[4], cubepoints[6], cubepoints[7], Color::Cyan },

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
    cpos.x = 0;
    cpos.y = 0;
    cpos.z = -500;
	s.setCameraPosition(cpos);
    
    cang.x = 0;
    cang.y = 0;
    cang.z = 0;
	s.setCameraAngle(cang);
 
	tft.setFOV(240); // Half the horizontal width is best
}

void loop() {
    cang.y+=2;
    if (cang.y >= 360) cang.y -= 360;
    cang.x++;
    if (cang.x >= 360) cang.x -= 360;
    
    s.setCameraAngle(cang);

    float beta = cang.x * (PI/180);
    float alpha = cang.y * (PI/180);
    int r = -500;
    cpos.x = r * cos(beta) * sin(alpha);
    cpos.z = r * cos(beta) * cos(alpha);
    cpos.y = -r * sin(beta);
    
    s.setCameraPosition(cpos);

    tft.startBuffer();
    tft.fillScreen(Color::Black);
    s.render(tft);
	tft.endBuffer();
	delay(50);
}

