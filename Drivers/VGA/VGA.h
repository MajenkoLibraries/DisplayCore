#ifndef _VGA_H
#define _VGA_H

#include <DisplayCore.h>

class VGA : public DisplayCore {
    public:
        static const uint16_t Width = 640;
        static const uint16_t Height = 480;
    private:
        static const uint32_t clockOffset = 10;

        // All these are in clock cycles
        static const uint32_t vgaHFP = 49 - clockOffset;   // Front porch == 49 clock cycles
        static const uint32_t vgaHSP = 293 - clockOffset;  // HSync pulse == 293 clock cycles
        static const uint32_t vgaHBP = 147 - clockOffset;  // Back porch == 147 clock cycles
        static const uint32_t vgaHDP = 1956 - clockOffset; // Display period == 1956 clock cycles
        // 2445 clock cycles in total

        static const uint32_t vgaHoriz[];

        // These are all in lines.
        static const uint32_t vgaVFP = 10;
        static const uint32_t vgaVSP = 2;
        static const uint32_t vgaVBP = 33;
        static const uint32_t vgaVDP = 480;

        static const uint32_t vgaVert[];
        static const uint32_t vgaOffset = 15;

        volatile uint8_t _buffer[Width/8 * Height];
        volatile uint8_t _line[Width/8 + 1];

        p32_ioport *_hsync_port;
        p32_ioport *_vsync_port;
        uint32_t _hsync_pin;
        uint32_t _vsync_pin;

    
    public:
        void process();
        void endPixelData();
        VGA(uint8_t hsync, uint8_t vsync);
        void initializeDevice();
        void setPixel(int16_t x, int16_t y, uint16_t c);
        void setRotation(uint8_t r) {}
        void displayOn() {}
        void displayOff() {}
        void invertDisplay(boolean i) {}

        uint16_t getWidth() { return Width; }
        uint16_t getHeight() { return Height; }

};

#endif
