#ifndef _VGA_H
#define _VGA_H

#include <DisplayCore.h>

#ifndef VGA_USE_DOUBLE_BUFFER
#define VGA_USE_DOUBLE_BUFFER 0
#endif

#ifndef VGA_USE_H_RES
#define VGA_USE_H_RES 0
#endif

#ifndef VGA_USE_V_RES
#define VGA_USE_V_RES 0
#endif

#ifdef __PIC32MZ__
#define _TIMER_5_IRQ _TIMER_5_VECTOR
#define _SPI4_TX_IRQ _SPI4_TX_VECTOR
#endif

class VGA : public DisplayCore {
    public:
        static const uint16_t Width = 768 / (VGA_USE_H_RES + 1);
        static const uint16_t Height = 480 / (VGA_USE_V_RES + 1);
    private:
        static const uint32_t clockOffset = 10;

        // All these are in clock cycles
        // For an 80 MHz chip each clock cycle is 13ns.

        static const uint32_t hoff = 10;

        // VGA timings specify:
        // Front porch = 636ns = 49 cycles
        static const uint32_t vgaHFP = 49 + 20 + hoff;
        // Pulse width = 3813ns = 293 cycles (240)
        static const uint32_t vgaHSP = 293;  // HSync pulse == 293 clock cycles
        // Back porch = 1907ns = 147 cycles
        static const uint32_t vgaHBP = 147 - hoff; // Back porch == 147 clock cycles
        // Whole line is 31778ns = 2444 cycles.
        static const uint32_t vgaHDP = 2444 - vgaHBP - vgaHSP - vgaHFP - 200; // Display period == 1956 clock cycles

        static const uint32_t vgaHoriz[];

        // These are all in lines.
        static const uint32_t vgaVFP = 10;
        static const uint32_t vgaVSP = 2;
        static const uint32_t vgaVBP = 33;
        static const uint32_t vgaVDP = 480;

        static const uint32_t vgaVert[];
        static const uint32_t vgaOffset = 45;

        volatile uint8_t _buffer0[((Width/8)+1) * Height] __attribute__((aligned(4)));
#if VGA_USE_DOUBLE_BUFFER
        volatile uint8_t _buffer1[((Width/8)+1) * Height] __attribute__((aligned(4)));
#endif

        volatile uint8_t *activeBuffer;

        uint32_t bufferNumber;

        p32_ioport *_hsync_port;
        p32_ioport *_vsync_port;
        uint32_t _hsync_pin;
        uint32_t _vsync_pin;

    
    public:
        VGA(uint8_t hsync, uint8_t vsync);
        void initializeDevice();
        void setPixel(int16_t x, int16_t y, uint16_t c);
        void setRotation(uint8_t r) {}
        void displayOn() {}
        void displayOff() {}
        void invertDisplay(boolean i) {}

        uint16_t getWidth() { return Width; }
        uint16_t getHeight() { return Height; }

        void vblank();
        void flip();

        void fillScreen(uint16_t c);

        uint32_t millis();

};

#endif
