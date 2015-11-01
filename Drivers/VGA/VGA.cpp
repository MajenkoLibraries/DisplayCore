#include <VGA.h>


#define VSYNC_OFF vgaVsyncPort->lat.set = vgaVsyncMask;
#define VSYNC_ON  vgaVsyncPort->lat.clr = vgaVsyncMask;

#define HSYNC_OFF vgaHsyncPort->lat.set = vgaHsyncMask;
#define HSYNC_ON  vgaHsyncPort->lat.clr = vgaHsyncMask;

VGA *_vgaDevice;

volatile uint8_t *vgaBuffer;
p32_ioport *vgaVsyncPort;
p32_ioport *vgaHsyncPort;
uint32_t vgaVsyncMask;
uint32_t vgaHsyncMask;

uint32_t vgaWidth;
uint32_t vgaHeight;
uint32_t vgaBufSize;

static const uint32_t VGA_TICK = 42; //49;
volatile uint32_t vgaScanLine = 0;
volatile uint32_t vgaMilliCount = 0;

void __USER_ISR __attribute((no_auto_psr)) vgaProcess() {
    static uint32_t ramPos = 0;

    // The current scan line on the display

    // The current portion of a scan line
    static uint32_t vgaScanPhase = 0;

    TMR5 = 0;
    IFS0bits.T5IF = 0;

    if (vgaScanPhase == 0) {
            if (vgaScanLine < 480) {
                DCH0SSA = ((uint32_t)&vgaBuffer[ramPos]) & 0x1FFFFFFF;
                DCH0ECONbits.CFORCE = 1;
                DCH0CONbits.CHEN = 1;
#if VGA_USE_DOUBLESCAN
                if (vgaScanLine & 1) 
#endif
                    ramPos += vgaWidth;
            }
            PR5 = VGA_TICK * 40; // 40 "ticks" later...
            vgaScanPhase++;
            return;
    } else if (vgaScanPhase == 1) {
            SPI4BUF = 0;
            PR5 = VGA_TICK * 1; // One tick later...
            vgaScanPhase++;
            return;
    } else if (vgaScanPhase == 2) {
            HSYNC_ON
            PR5 = VGA_TICK * 6; // 6 ticks later...
            vgaScanPhase++;
            return;
    } else if (vgaScanPhase == 3) {
            HSYNC_OFF
            PR5 = VGA_TICK * 3; // 3 ticks later it's back to the start.
            vgaScanPhase = 0;
            vgaScanLine++;
    }


    if (vgaScanLine == 490) {
        ramPos = 0;
        VSYNC_ON
        while (TMR4 >= 312) {
            vgaMilliCount++;
            TMR4 -= 312;
        }
    } else if (vgaScanLine == 492) {
        VSYNC_OFF
    } else if (vgaScanLine == 525) {
        vgaScanLine = 0;
    }
}

uint32_t VGA::millis() {
    return vgaMilliCount;
}

void VGA::initializeDevice() {
    _vgaDevice = this;
    if (_hsync_pin == 0 || _vsync_pin == 0) {
        return;
    }

    memset((void *)_buffer0, 0, ((Width/8)+1) * Height);

#if VGA_USE_DOUBLE_BUFFER
    memset((void *)_buffer1, 0, ((Width/8)+1) * Height);
    bufferNumber = 0;
    activeBuffer = _buffer0;
    vgaBuffer = _buffer1;
#else
    bufferNumber = 0;
    activeBuffer = _buffer0;
    vgaBuffer = _buffer0;
#endif

    _hsync_port->tris.clr = _hsync_pin;
    _vsync_port->tris.clr = _vsync_pin;

    // First we need to set up a timer that will trigger at the different times.
    T5CONbits.TCKPS = 0; // No prescaler
    PR5 = 0xFFFF;

    setIntVector(_TIMER_5_VECTOR, vgaProcess);
    setIntPriority(_TIMER_5_VECTOR, 7, 3);
    clearIntFlag(_TIMER_5_IRQ);
    setIntEnable(_TIMER_5_IRQ);

    // Now congfigure SPI4 for display data transmission.
    SPI4CON = 0;
    SPI4CONbits.MSTEN = 1;
    SPI4CONbits.STXISEL = 0b11; // Interrupt when one byte in buffer
#if VGA_USE_HI_RES
    SPI4BRG = 0; // This will set how big each pixel is.
#elif VGA_USE_LO_RES
    SPI4BRG = 2;
#else
    SPI4BRG = 1; // This will set how big each pixel is.
#endif
    SPI4CONbits.ON = 1;

    // And now a DMA channel for transferring the data
    DCH0SSA = ((unsigned int)vgaBuffer) & 0x1FFFFFFF;
    DCH0DSA = ((unsigned int)&SPI4BUF) & 0x1FFFFFFF;
    DCH0SSIZ = (Width / 8) + 1;
    DCH0DSIZ = 1;
    DCH0CSIZ = 1;
    DCH0ECONbits.SIRQEN = 1;
    DCH0ECONbits.CHSIRQ = _SPI4_TX_IRQ;
    DCH0CONbits.CHAEN = 0;
    DCH0CONbits.CHEN = 0;
    DCH0CONbits.CHPRI = 3;

    vgaVsyncPort = _vsync_port;
    vgaHsyncPort = _hsync_port;
    vgaVsyncMask = _vsync_pin;
    vgaHsyncMask = _hsync_pin;
    vgaWidth = (Width/8) + 1;
    vgaHeight = Height;
    vgaBufSize = vgaWidth * vgaHeight;


    VSYNC_OFF
    HSYNC_OFF

    DMACONbits.ON = 1;
    T5CONbits.ON = 1; // Turn on the timer

    // Unfortunately the core timer really plays havoc with the VGA timing.
    // So we have to disable it. That means no millis() and no delay().
    // Makes things a little more interesting...
    clearIntEnable(_CORE_TIMER_IRQ);
    
    // To compensate we'll create our own millis system that is keyed to the
    // display vertical sync.
    T4CONbits.TCKPS = 7; // 256:1 prescale
    TMR4 = 0;
    T4CONbits.ON = 1;
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
    uint32_t poff = (x + y * (Width + 8)) / 8;
    uint8_t ppos = x % 8;
    activeBuffer[poff] &= ~(0x80>>ppos);
    if (c) {
        activeBuffer[poff] |= (0x80>>ppos);
    }
}

void VGA::vblank() {
    while (vgaScanLine != 480);
}

void VGA::flip() {
    vblank();
#if VGA_USE_DOUBLE_BUFFER
    bufferNumber = 1 - bufferNumber;
    if (bufferNumber == 0) {
        vgaBuffer = _buffer1;
        activeBuffer = _buffer0;
    } else {
        vgaBuffer = _buffer0;
        activeBuffer = _buffer1;
    }
#endif
}

void VGA::fillScreen(uint16_t c) {
    if (c) {
        for (uint32_t line = 0; line < Height; line++) {
            memset((void *)activeBuffer + (line * ((Width/8)+1)), 0xFF, (Width/8));
        }
    } else {
        for (uint32_t line = 0; line < Height; line++) {
            memset((void *)activeBuffer + (line * ((Width/8)+1)), 0x00, (Width/8));
        }
    }
}

