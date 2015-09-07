#include <Picadillo.h>

Picadillo tft;
 
int
  bits        = 12,   // Fractional resolution
  pixelWidth  = Picadillo::Height,  // LCD dimensions
  pixelHeight = Picadillo::Width,
  iterations  = 100;  // Fractal iteration limit or 'dwell'
float
  centerReal  = -0.6, // Image center point in complex plane
  centerImag  =  0.4,
  rangeReal   =  1.5, // Image coverage in complex plane
  rangeImag   =  1.5;
 
void setup()
{
	tft.initializeDevice();
    tft.setBacklight(255);
	tft.setRotation(1);
	tft.fillScreen(Color::Black);
}
 
void loop()
{
	int           x,y,n;
	long          a,b,a2,b2,posReal,posImag,startTime,elapsedTime;
long
  startReal   = (long)((centerReal - rangeReal * 0.5)   * (float)(1 << bits)),
  startImag   = (long)((centerImag + rangeImag * 0.5)   * (float)(1 << bits)),
  incReal     = (long)((rangeReal / (float)pixelWidth)  * (float)(1 << bits)),
  incImag     = (long)((rangeImag / (float)pixelHeight) * (float)(1 << bits));
 
	posImag = startImag;
	for(y = 0; y < pixelHeight; y++) {
    	posReal = startReal;
    	for(x = 0; x < pixelWidth; x++) {
      		a = posReal;
      		b = posImag;
      		for(n = iterations; n > 0 ; n--) {
        		a2 = (a * a) >> bits;
        		b2 = (b * b) >> bits;
        		if((a2 + b2) >= (4 << bits)) {
        			break;
        		}
    			b  = posImag + ((a * b) >> (bits - 1));
    			a  = posReal + a2 - b2;
  			}
      		tft.setPixel(x, y, n ? (iterations - n) * 200 : Color::Black);
	      	posReal += incReal;
		}
		posImag -= incImag;
	}
	delay(1000);
}
