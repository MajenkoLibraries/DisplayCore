
// We can only compile this code if we have both a
// DMA system and the Parallel Master Port.
#ifdef _BOARD_PICADILLO_35T_
#include <Picadillo.h>

void Picadillo::writeCommand(uint16_t c) {
    while (PMMODEbits.BUSY == 1);
    PMADDR = 0x0000;
    PMDIN = c;
}

void Picadillo::writeData(uint16_t c) {
    while (PMMODEbits.BUSY == 1);
    PMADDR = 0x0001;
    PMDIN = c;
}

//==============================================================
// Initialise HX8357 LCD Driver IC
//==============================================================
void Picadillo::initializeDevice() 
{
    PMCONbits.ON = 0;
    asm volatile("nop");

    PMCONbits.PTWREN = 1;
    PMCONbits.PTRDEN = 1;
    PMCONbits.CSF = 0;

    PMAEN = 0x0001; // Enable PMA0 pin for RS pin and CS1 as CS

    PMMODEbits.MODE16 = 1;
    PMMODEbits.MODE = 0b10;
    PMMODEbits.WAITB = 0;
    PMMODEbits.WAITM = 0;
    PMMODEbits.WAITE = 0;

    //PMADDR = 0; // Set current address to 0
    PMADDR = 0x0000; // Set current address to 0, CS1 Active

    PMCONbits.ON = 1;

    _width  = Picadillo::Width;
    _height = Picadillo::Height;
	
	colstart = 0;  //NEED TO CONFIRM
    rowstart = 0;  //NEED TO CONFIRM
	
    writeCommand(HX8357_EXIT_SLEEP_MODE); //Sleep Out
    delay(150);
	writeCommand(HX8357_ENABLE_EXTENSION_COMMAND);
	writeData(0xFF);
	writeData(0x83);
	writeData(0x57);
	delay(1);
	writeCommand(HX8357_SET_POWER_CONTROL);
	writeData(0x00);
	writeData(0x12);
	writeData(0x12);
	writeData(0x12);
	writeData(0xC3);
	writeData(0x44);
	delay(1);
	writeCommand(HX8357_SET_DISPLAY_MODE);
	writeData(0x02);
	writeData(0x40);
	writeData(0x00);
	writeData(0x2A);
	writeData(0x2A);
	writeData(0x20);
	writeData(0x91);
	delay(1);
	writeCommand(HX8357_SET_VCOM_VOLTAGE);
	writeData(0x38);
	delay(1);
	writeCommand(HX8357_SET_INTERNAL_OSCILLATOR);
	writeData(0x68);
	writeCommand(0xE3); //Unknown Command
	writeData(0x2F);
	writeData(0x1F);
	writeCommand(0xB5); //Set BGP
	writeData(0x01);
	writeData(0x01);
	writeData(0x67);
	writeCommand(HX8357_SET_PANEL_DRIVING);
	writeData(0x70);
	writeData(0x70);
	writeData(0x01);
	writeData(0x3C);
	writeData(0xC8);
	writeData(0x08);
	delay(1);
	writeCommand(0xC2); // Set Gate EQ
	writeData(0x00);
	writeData(0x08);
	writeData(0x04);
	delay(1);
	writeCommand(HX8357_SET_PANEL_CHARACTERISTIC);
	writeData(0x09);
	delay(1);
	writeCommand(HX8357_SET_GAMMA_CURVE);
	writeData(0x01);
	writeData(0x02);
	writeData(0x03);
	writeData(0x05);
	writeData(0x0E);
	writeData(0x22);
	writeData(0x32);
	writeData(0x3B);
	writeData(0x5C);
	writeData(0x54);
	writeData(0x4C);
	writeData(0x41);
	writeData(0x3D);
	writeData(0x37);
	writeData(0x31);
	writeData(0x21);
	writeData(0x01);
	writeData(0x02);
	writeData(0x03);
	writeData(0x05);
	writeData(0x0E);
	writeData(0x22);
	writeData(0x32);
	writeData(0x3B);
	writeData(0x5C);
	writeData(0x54);
	writeData(0x4C);
	writeData(0x41);
	writeData(0x3D);
	writeData(0x37);
	writeData(0x31);
	writeData(0x21);
	writeData(0x00);
	writeData(0x01);
	delay(1);
	writeCommand(HX8357_SET_PIXEL_FORMAT); //COLMOD RGB888
	writeData(0x55);
	writeCommand(HX8357_SET_ADDRESS_MODE);
	writeData(0x00);
	writeCommand(HX8357_SET_TEAR_ON); //TE ON
	writeData(0x00);
	delay(10);
	writeCommand(HX8357_SET_DISPLAY_ON); //Display On
	delay(10);
    clearClipping();
}

void Picadillo::setAddrWindow(int x0, int y0, int x1, int y1) 
{
    writeCommand(HX8357_SET_COLUMN_ADDRESS); // Column addr set
    writeData((x0+colstart) >> 8);
    writeData(x0+colstart);     // XSTART 
    writeData((x1+colstart) >> 8);
    writeData(x1+colstart);     // XEND

    writeCommand(HX8357_SET_PAGE_ADDRESS); // Row addr set
    writeData((y0+rowstart) >> 8);
    writeData(y0+rowstart);     // YSTART
    writeData((y1+rowstart) >> 8);
    writeData(y1+rowstart);     // YEND
	writeCommand(HX8357_WRITE_MEMORY_START); //Write SRAM Data
}

void Picadillo::setPixel(int x, int y, color_t color) 
{
	if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) 
		return;
    if ((x < _clip_x0) || (x > _clip_x1) || (y < _clip_y0) || (y > _clip_y1)) 
        return;
	setAddrWindow(x,y,x+1,y+1);
    PMADDR = 0x0001;
    PMDIN = color;
}

void Picadillo::fillScreen(color_t color) 
{
	fillRectangle(0, 0,  _width, _height, color);
}

void Picadillo::fillRectangle(int x, int y, int w, int h, color_t color) 
{
    if (!clipToScreen(x, y, w, h)) {
        return;
    }
	setAddrWindow(x, y, x+w-1, y+h-1);

    PMADDR = 0x0001;
	for(y=h; y>0; y--) {
		for(x=w; x>0; x--) {
            PMDIN = color;
		}
	}
}

void Picadillo::drawHorizontalLine(int x, int y, int w, color_t color) 
{
    int h = 1;
    if (!clipToScreen(x, y, w, h)) {
        return;
    }
	setAddrWindow(x, y, x+w-1, y);

    PMADDR = 0x0001;
	while (w--) {
		PMDIN = color;
	}
}

void Picadillo::drawVerticalLine(int x, int y, int h, color_t color) 
{
    int w = 1;
    if (!clipToScreen(x, y, w, h)) {
        return;
    }
	setAddrWindow(x, y, x, y+h-1);

    PMADDR = 0x0001;
	while (h--) {
        PMDIN = color;
	}
}

void Picadillo::setRotation(int m) 
{
	writeCommand(HX8357_SET_ADDRESS_MODE);
	rotation = m % 4; // can't be higher than 3
	switch (rotation) 
	{
		case 0:
			//PORTRAIT
			writeData(0x0000);
			_width  = Picadillo::Width;
			_height = Picadillo::Height;
			break;
		case 1:
		    //LANDSCAPE
			writeData(0x0060);
			_width  = Picadillo::Height;
			_height = Picadillo::Width;
			break;
		case 2:	
			//UPSIDE DOWN PORTRAIT
			writeData(0x00C0);
			_width  = Picadillo::Width;
			_height = Picadillo::Height;
			break;
		case 3:
			//UPSIDE DOWN LANDSCAPE
			writeData(0x00A0);
			_width  = Picadillo::Height;
			_height = Picadillo::Width;
			break;
	}
    clearClipping();
}

void Picadillo::invertDisplay(boolean i) 
{
	writeCommand(i ? HX8357_INVON : HX8357_INVOFF);
}

void Picadillo::displayOn() 
{
	writeCommand(HX8357_DISPLAYON);
}

void Picadillo::displayOff() 
{
	writeCommand(HX8357_DISPLAYOFF);
}

void Picadillo::openWindow(int x0, int y0, int x1, int y1) {
    setAddrWindow(x0, y0, x0 + x1 - 1, y0 + y1 - 1);
    PMADDR = 0x0001;
}

void Picadillo::windowData(color_t d) {
    PMDIN = d;
}

void Picadillo::windowData(color_t *d, int l) {
//    for (uint32_t i = 0; i < l; i++) {
//        while (PMMODEbits.BUSY == 1);
//        PMDIN = d[i];
//    }
//    return;
    uint32_t toXfer = l * 2;

    uint16_t *data = d;

    while (toXfer > 0) {
        while (DCH3CONbits.CHBUSY);
        uint32_t chunk = toXfer;
        if (chunk > 65534) {
            chunk = 65534;
        }

        toXfer -= chunk;

        PMMODEbits.IRQM = 0b01;

        DCH3INTbits.CHSDIE = 1;
        DCH3SSA = ((uint32_t)data) & 0x1FFFFFFF;
        DCH3DSA = ((uint32_t)&PMDIN) & 0x1FFFFFFF;
        DCH3SSIZ = chunk;
        DCH3DSIZ = 2;
        DCH3CSIZ = 2;
        DCH3ECONbits.SIRQEN = 1;
        DCH3ECONbits.CHSIRQ = _PMP_IRQ;
        DCH3CONbits.CHAEN = 0;
        DCH3CONbits.CHEN = 1;

        DMACONbits.ON=1;

        DCH3ECONbits.CFORCE = 1;
        data += (chunk >> 1);
    }
}

void Picadillo::closeWindow() {
    if (DCH3CONbits.CHEN == 1) {
        while (DCH3CONbits.CHBUSY);
        DCH3CONbits.CHEN = 0;
    }
}

uint8_t Picadillo::readByte(boolean fresh) {
    static boolean haveStoredByte = false;
    static uint8_t storedByte = 0;
    if (fresh) {
        haveStoredByte = false;
    }
    if (!haveStoredByte) {
        while (PMMODEbits.BUSY == 1);
        uint16_t din = PMDIN;
        storedByte = din & 0xFF;
        haveStoredByte = true;
        return din >> 8;
    }
    haveStoredByte = false;
    return storedByte;
}

color_t Picadillo::colorAt(int x, int y) {
	if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) 
		return 0;
    setAddrWindow(x, y, x, y);
    writeCommand(HX8357_READ_MEMORY_START);
    readData(false);
    readByte(true);
    readByte();
    readByte();
    readByte();
    readByte();

    uint8_t r = readByte();
    uint8_t g = readByte();
    uint8_t b = readByte();

    return rgb(r, g, b);
}
void Picadillo::getRectangle(int x, int y, int w, int h, color_t *buf) {
    uint32_t i = 0;
    for (int py = 0; py < h; py++) {
        for (int px = 0; px < w; px++) {
            buf[i++] = colorAt(x + px, y + py);
        }
    }
}

uint16_t Picadillo::readData(boolean cont) {
    uint16_t din;
    PMADDR = 0x0001;
    if (!cont) {
        while (PMMODEbits.BUSY == 1);
        din = PMDIN;
    }
    while (PMMODEbits.BUSY == 1);
    din = PMDIN;
    return din;
}

void Picadillo::enableBacklight() {
    analogWrite(PIN_BACKLIGHT, _brightness);
}

void Picadillo::disableBacklight() {
    analogWrite(PIN_BACKLIGHT, 0);
}

void Picadillo::setBacklight(int b) {
    _brightness = b;
    analogWrite(PIN_BACKLIGHT, _brightness);
}

int Picadillo::getScanLine() {
    writeCommand(HX8357_GETSCAN);
    uint8_t h = readData(false);
    uint8_t l = readByte(true);
    return (h << 8) | l;
}

#endif
