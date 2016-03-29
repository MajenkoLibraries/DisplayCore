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

triangle cube[12] = {
    { cubepoints[0], cubepoints[1], cubepoints[3], Color::Red },
    { cubepoints[0], cubepoints[3], cubepoints[2], Color::Red },

    { cubepoints[0], cubepoints[6], cubepoints[4], Color::Green },
    { cubepoints[0], cubepoints[2], cubepoints[6], Color::Green },

    { cubepoints[0], cubepoints[5], cubepoints[1], Color::Blue },
    { cubepoints[0], cubepoints[4], cubepoints[5], Color::Blue },

    { cubepoints[1], cubepoints[7], cubepoints[3], Color::Yellow },
    { cubepoints[1], cubepoints[5], cubepoints[7], Color::Yellow },

    { cubepoints[2], cubepoints[7], cubepoints[6], Color::Magenta },
    { cubepoints[2], cubepoints[3], cubepoints[7], Color::Magenta },

    { cubepoints[4], cubepoints[7], cubepoints[5], Color::Cyan },
    { cubepoints[4], cubepoints[6], cubepoints[7], Color::Cyan },

};

Scene s(cube, sizeof(cube) / sizeof(cube[0]));

point3d cpos;
point3d cang;
point3d lpos;
point3d lang;

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
    s.setAmbientLight(0.5);
	tft.setFOV(240); // Half the horizontal width is best
}

void loop() {
    cang.y+=2;
    if (cang.y >= 360) cang.y -= 360;
    cang.x++;
    if (cang.x >= 360) cang.x -= 360;
    
    s.setCameraAngle(cang);

    lang.y++;
    if (lang.y >= 360) lang.y -= 360;
    lang.x+=2;
    if (lang.x >= 360) lang.x -= 360;

    float beta = cang.x * (PI/180);
    float alpha = cang.y * (PI/180);
    int r = 500;
    cpos.x = r * cos(beta) * sin(alpha);
    cpos.z = r * cos(beta) * cos(alpha);
    cpos.y = -r * sin(beta);
    
    s.setCameraPosition(cpos);

    beta = lang.x * (PI/180);
    alpha = lang.y * (PI/180);
    r = 1000;
    lpos.x = r * cos(beta) * sin(alpha);
    lpos.z = r * cos(beta) * cos(alpha);
    lpos.y = -r * sin(beta);
    
    s.setLightPosition(lpos);


    tft.startBuffer();
    tft.fillScreen(Color::Black);  
    s.render(tft);
	tft.endBuffer();
	delay(100);
}

