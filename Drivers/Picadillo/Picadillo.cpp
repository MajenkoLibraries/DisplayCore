#include <Picadillo.h>

//--------------------------------------------------------------------------//
// HX8357 Driver Registers
//--------------------------------------------------------------------------//
#define HX8357_EXIT_SLEEP_MODE          	0x11
#define HX8357_SET_DISPLAY_OFF          	0x28
#define HX8357_SET_DISPLAY_ON           	0x29
#define HX8357_SET_COLUMN_ADDRESS       	0x2A
#define HX8357_SET_PAGE_ADDRESS         	0x2B
#define HX8357_WRITE_MEMORY_START       	0x2C
#define HX8357_READ_MEMORY_START        	0x2E
#define HX8357_SET_TEAR_ON              	0x35
#define HX8357_SET_ADDRESS_MODE         	0x36
#define HX8357_SET_PIXEL_FORMAT         	0x3A
#define HX8357_WRITE_MEMORY_CONTINUE    	0x3C
#define HX8357_READ_MEMORY_CONTINUE     	0x3E
#define HX8357_SET_INTERNAL_OSCILLATOR   	0xB0
#define HX8357_SET_POWER_CONTROL         	0xB1
#define HX8357_SET_DISPLAY_MODE          	0xB4
#define HX8357_SET_VCOM_VOLTAGE         	0xB6
#define HX8357_ENABLE_EXTENSION_COMMAND 	0xB9
#define HX8357_SET_PANEL_DRIVING        	0xC0    // not documented!
#define HX8357_SET_PANEL_CHARACTERISTIC  	0xCC
#define HX8357_SET_GAMMA_CURVE           	0xE0

#define HX8357_INVON 						0x21
#define HX8357_INVOFF						0x20
#define HX8357_DISPLAYOFF					0x28
#define HX8357_DISPLAYON					0x29

void inline Picadillo::writeCommand(uint16_t c) {
    while (PMMODEbits.BUSY == 1);
    PMADDR = 0x0000;
    PMDIN = c;
    _lastOp = opWrite;
}

void inline Picadillo::writeData(uint16_t c) {
    while (PMMODEbits.BUSY == 1);
    PMADDR = 0x0001;
    PMDIN = c;
    _lastOp = opWrite;
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
	writeCommand(HX8357_WRITE_MEMORY_START); //Write SRAM Data
    _cacheState = cacheInvalid;
    clearClipping();
}

void Picadillo::setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) 
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

void Picadillo::setAddrWindowRead(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) 
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

    writeCommand(HX8357_READ_MEMORY_START); //Read SRAM Data
}

void Picadillo::setPixel(int16_t x, int16_t y, uint16_t color) 
{
	if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) 
		return;
    if ((x < _clip_x0) || (x > _clip_x1) || (y < _clip_y0) || (y > _clip_y1)) 
        return;
	setAddrWindow(x,y,x+1,y+1);
    PMADDR = 0x0001;
    PMDIN = color;
    _lastOp = opWrite;
    _cacheState = cacheInvalid;
}

void Picadillo::fillScreen(uint16_t color) 
{
	fillRectangle(0, 0,  _width, _height, color);
    _cacheState = cacheInvalid;
}

void Picadillo::fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) 
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
    _lastOp = opWrite;
    _cacheState = cacheInvalid;
}

void Picadillo::drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color) 
{
    int16_t h = 1;
    if (!clipToScreen(x, y, w, h)) {
        return;
    }
	setAddrWindow(x, y, x+w-1, y);

    PMADDR = 0x0001;
	while (w--) {
		PMDIN = color;
	}
    _lastOp = opWrite;
    _cacheState = cacheInvalid;
}

void Picadillo::drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color) 
{
    int16_t w = 1;
    if (!clipToScreen(x, y, w, h)) {
        return;
    }
	setAddrWindow(x, y, x, y+h-1);

    PMADDR = 0x0001;
	while (h--) {
        PMDIN = color;
	}
    _lastOp = opWrite;
    _cacheState = cacheInvalid;
}

void Picadillo::setRotation(uint8_t m) 
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
    _cacheState = cacheInvalid;
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

void Picadillo::openWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    setAddrWindow(x0, y0, x0 + x1 - 1, y0 + y1 - 1);
    PMADDR = 0x0001;
}

void Picadillo::windowData(uint16_t d) {
    PMDIN = d;
    _lastOp = opWrite;
}

void Picadillo::windowData(uint16_t *d, uint32_t l) {

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
#ifdef __PIC32MX__
        DCH3ECONbits.CHSIRQ = _PMP_IRQ;
#endif
        DCH3CONbits.CHAEN = 0;
        DCH3CONbits.CHEN = 1;

        DMACONbits.ON=1;

        DCH3ECONbits.CFORCE = 1;
        data += (chunk >> 1);
    }

//    for (uint32_t i = 0; i < l; i++) {
//        PMDIN = d[i];
//    }
    _lastOp = opWrite;
    _cacheState = cacheInvalid;
}

void Picadillo::closeWindow() {
    if (DCH3CONbits.CHEN == 1) {
        while (DCH3CONbits.CHBUSY);
        DCH3CONbits.CHEN = 0;
    }
}


uint16_t Picadillo::colorAt(int16_t x, int16_t y) {
	if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) 
		return 0;
    loadCacheBlock(x, y);

    int16_t xo = x & ((1 << Picadillo::cacheDimension) - 1);
    int16_t yo = y & ((1 << Picadillo::cacheDimension) - 1);

    uint32_t offset = yo * (1 << Picadillo::cacheDimension) + xo;

    return _cacheData[offset];
}

extern Picadillo tft;
void Picadillo::loadCacheBlock(int16_t x, int16_t y) {
    int16_t x0 = x & ~((1 << cacheDimension) - 1);
    int16_t y0 = y & ~((1 << cacheDimension) - 1);
    int16_t x1 = x0 + ((1 << cacheDimension) - 1);
    int16_t y1 = y0 + ((1 << cacheDimension) - 1);

    if (
        (x >= _cacheX) && 
        (x < _cacheX + (1 << cacheDimension))  && 
        (y >= _cacheY) && 
        (y < _cacheY + (1 << cacheDimension)) && 
        (_cacheState != cacheInvalid)
    ) {
        return;
    }

    if (_cacheState == cacheDirty) {
        flushCacheBlock();
    }


	setAddrWindowRead(x0,y0,x1,y1);
    _lastOp = opRead;
    PMADDR = 0x0001;
    (void) PMDIN;

    for (int i = 0; i < 5; i++) {
        while (PMMODEbits.BUSY == 1);
        (void) PMDIN;
    }

    uint16_t values[96];
    uint32_t vc = 0;

    for (uint32_t cpos = 0; cpos < ((1 << cacheDimension) * (1 << cacheDimension)); cpos+=2) {
        while (PMMODEbits.BUSY == 1);
        uint16_t val1 = PMDIN;
        values[vc++] = val1;
        while (PMMODEbits.BUSY == 1);
        uint16_t val2 = PMDIN;
        values[vc++] = val2;
        while (PMMODEbits.BUSY == 1);
        uint16_t val3 = PMDIN;
        values[vc++] = val3;

        
        _cacheData[cpos] = rgb(val1 >> 8, val1 & 0xFF, val2 >> 8);
        _cacheData[cpos+1] = rgb(val2 & 0xFF, val3 >> 8, val3 & 0xFF);
    }
    _cacheState = cacheClean;
    _cacheX = x0;
    _cacheY = y0;
//    tft.setCursor(0, 0);
//    tft.print("Block: ");
//    tft.print(x0); tft.print("-"); tft.print(y0); tft.print(" to ");
//    tft.print(x1); tft.print("-"); tft.println(y1);

//    drawRectangle(x0, y0, (1 << cacheDimension), (1 << cacheDimension), Color::Red);
//    for (int i = 0; i < 96; i++) {
//        sprintf(temp, "%04X ", values[i]);
//        tft.print(temp);
//    }
//    delay(1000);
}

void Picadillo::flushCacheBlock() {
    if (_cacheState != cacheDirty) {
        return;
    }
    openWindow(_cacheX, _cacheY, 1 << cacheDimension, 1 << cacheDimension);
    windowData(_cacheData, ((1 << cacheDimension) * (1 << cacheDimension)));
    closeWindow();
    _cacheState = cacheClean;
}


