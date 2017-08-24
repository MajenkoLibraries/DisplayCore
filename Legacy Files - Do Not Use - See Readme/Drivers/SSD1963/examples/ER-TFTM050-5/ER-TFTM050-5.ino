#include <SSD1963.h>
#include <XPT2046.h>

DSPI0 spi;

// example tested on Uno32 using a ER-TFTM050-5 display. This one has a 24 bit TFT bus width.

// touch screen
// for SPI port:
// CS on pin 41   
// SDO2 on pin 11  J8-1
// SDI2 on pin 12  J8-4
// SCK2 on pin 13  J8-3 (also on some LED)
XPT2046 ts(spi, 41, 800, 480);

// LCD

//SSD1963(
//            uint8_t rs, uint8_t wr, uint8_t rd, uint8_t cs, uint8_t reset,
//            uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
//            uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
//            uint8_t d8, uint8_t d9, uint8_t d10, uint8_t d11,
//            uint8_t d12, uint8_t d13, uint8_t d14, uint8_t d15,
//           uint8_t tft_bus_width = TFTBUS18
//        );

// run in 16 bit mode (tft bus width defaults to TFTBUS18).
//SSD1963 tft(35, 37, 36, 34, 38,     7, 33, 6, 32, 5, 31, 4, 30, 3, 29, 2, 28, 9, 27, 8, 26);
//         rs  wr  rd  cs  reset  d0  d1 d2 ...
//  if you don't have RS but you do have D/C - those are two different names for the same thing ("Data / Command", and "Register Select").

// run in 16 bit mode (specifying tft bus width)
SSD1963 tft(35, 37, 36, 34, 38,     7, 33, 6, 32, 5, 31, 4, 30, 3, 29, 2, 28, 9, 27, 8, 26, TFTBUS24); // TFTBUS24 or TFTBUS18
//         rs  wr  rd  cs  reset  d0  d1 d2 ...

// run in 8 bit mode (specifying tft bus width)
//SSD1963 tft(35, 37, 36, 34, 38,    7,33, 6, 32, 5, 31, 4, 30,TFTBUS24); // TFTBUS24 or TFTBUS18

void setup() {
   tft.initializeDevice();
   tft.setBacklight(255);
   ts.initializeDevice();
   ts.offsetX(-20);
   ts.offsetY(-20);
   ts.scaleX(1.1);
   ts.scaleY(1.1);
}

uint16_t color = 0b1111100000000000;   // 5 bits blue; 6bits green; 5 bits red

void loop() {
tft.fillCircle(rand()%900, rand()%500, rand()%50, rand());
ts.sample();
if (ts.isPressed()) {
   tft.fillCircle(ts.x(), ts.y(), 50, color);
   }
}


