#include <VGA.h>


#define VSYNC_OFF _vsync_port->lat.clr = _vsync_pin;
#define VSYNC_ON  _vsync_port->lat.set = _vsync_pin;

#define HSYNC_OFF _hsync_port->lat.clr = _hsync_pin;
#define HSYNC_ON  _hsync_port->lat.set = _hsync_pin;

VGA *_vgaDevice;

const uint32_t VGA::vgaHoriz[] = {
    vgaHFP, vgaHSP, vgaHBP, vgaHDP
};

const uint32_t VGA::vgaVert[] = {
    vgaVFP,
    vgaVFP + vgaVSP,
    vgaVFP + vgaVSP + vgaVBP,
    vgaVFP + vgaVSP + vgaVBP + vgaVDP
};


void __USER_ISR vgaProcess() {
    _vgaDevice->process();
}

void VGA::process() {

    static uint32_t ramPos = 0;
    static uint32_t ramPS = 0;

    // The current scan line on the display
    static uint32_t vgaScanLine = 0;

    // The current portion of a scan line
    static uint32_t vgaScanPhase = 0;

    TMR2 = 0;
    IFS0bits.T2IF = 0;
    vgaScanPhase++;

    if (vgaScanPhase == 4) {
        vgaScanPhase = 0;
        vgaScanLine++;
    }

    PR2 = vgaHoriz[vgaScanPhase];

    if (vgaScanPhase == 1) {
        HSYNC_ON
    } else {
        HSYNC_OFF
    }

    if (vgaScanLine == 10) {
        VSYNC_ON
    } else if (vgaScanLine == 12) {
        VSYNC_OFF
        ramPos = 0;
    } else if ((vgaScanLine >= vgaOffset) && (vgaScanLine < (vgaOffset + 480))) {
        if (vgaScanPhase == 1) {
            memcpy((void *)_line, (void *)&_buffer[ramPos], 80);
            _line[80] = 0;
            ramPos += 80;
        } else if (vgaScanPhase == 3) {
//            SPI4CONbits.ON = 1;
            DCH0SSA = ((uint32_t)_line) & 0x1FFFFFFF;
            DCH0ECONbits.CFORCE = 1;
            DCH0CONbits.CHEN = 1;
        }
    } else if (vgaScanLine == 525) {
        vgaScanLine = 0;
    }
}

void __USER_ISR vgaEndPixelData() {
    _vgaDevice->endPixelData();
}

void VGA::endPixelData() {
    DCH0INTbits.CHSDIF = 0;
    IFS1bits.DMA0IF = 0;
}

void VGA::initializeDevice() {
    _vgaDevice = this;
    if (_hsync_pin == 0 || _vsync_pin == 0) {
        return;
    }

    _hsync_port->tris.clr = _hsync_pin;
    _vsync_port->tris.clr = _vsync_pin;

    // First we need to set up a timer that will trigger at the different times.
    T2CONbits.TCKPS = 0; // No prescaler
    PR2 = vgaHoriz[0]; // Initial timeout is the length of the front porch

    setIntVector(_TIMER_2_VECTOR, vgaProcess);
    setIntPriority(_TIMER_2_VECTOR, 7, 3);
    clearIntFlag(_TIMER_2_IRQ);
    setIntEnable(_TIMER_2_IRQ);

    VSYNC_OFF
    HSYNC_OFF

    // Now congfigure SPI4 for display data transmission.
    SPI4CON = 0;
    SPI4CONbits.MSTEN = 1;
    SPI4CONbits.STXISEL = 0b11; // Interrupt when one byte in buffer
    SPI4BRG = 1; // This will set how big each pixel is.
    SPI4CONbits.ON = 1;

    // And now a DMA channel for transferring the data
    DCH0SSA = ((unsigned int)_buffer) & 0x1FFFFFFF;
    DCH0DSA = ((unsigned int)&SPI4BUF) & 0x1FFFFFFF;
    DCH0SSIZ = 81;
    DCH0DSIZ = 1;
    DCH0CSIZ = 1;
    DCH0ECONbits.SIRQEN = 1;
    DCH0ECONbits.CHSIRQ = _SPI4_TX_IRQ;
    DCH0CONbits.CHAEN = 0;
    DCH0CONbits.CHEN = 0;
    DCH0CONbits.CHPRI = 3;

    DCH0INTbits.CHSDIF = 0;
    DCH0INTbits.CHSDIE = 1;

    clearIntFlag(_DMA0_IRQ);
    setIntVector(_DMA_0_VECTOR, (isrFunc)vgaEndPixelData);
    setIntPriority(_DMA_0_VECTOR, 6, 0);
    setIntEnable(_DMA0_IRQ);

    DMACONbits.ON = 1;
    T2CONbits.ON = 1; // Turn on the timer
}

VGA::VGA(uint8_t hsync, uint8_t vsync) {
    uint32_t port = 0;

    _hsync_pin = 0;
    _vsync_pin = 0;

    if (hsync >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    if (vsync >= NUM_DIGITAL_PINS_EXTENDED) { return; }

    port = digitalPinToPort(hsync);
    if (port == NOT_A_PIN) { return; }
    _hsync_port = (p32_ioport *)portRegisters(port);
    _hsync_pin = digitalPinToBitMask(hsync);

    port = digitalPinToPort(vsync);
    if (port == NOT_A_PIN) { return; }
    _vsync_port = (p32_ioport *)portRegisters(port);
    _vsync_pin = digitalPinToBitMask(vsync);
}

void VGA::setPixel(int16_t x, int16_t y, uint16_t c) {
    if (x < 0 || y < 0 || x >= Width || y >= Height) {
        return;
    }
    uint32_t poff = (x + y * Width) / 8;
    uint8_t ppos = x % 8;
    _buffer[poff] &= ~(0x80>>ppos);
    if (c) {
        _buffer[poff] |= (0x80>>ppos);
    }
}
