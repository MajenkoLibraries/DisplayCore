#ifndef _PG25664CG_H
#define _PG25664CG_H

#include <DisplayCore.h>

/*
D/C     A0
WR      A1
RD      A2
D0      37      RE0
D1      36      RE1
D2      35      RE2
D3      34      RE3
D4      33      RE4
D5      32      RE5
D6      31      RE6
D7      30      RE7
CS      A3
RES     A4
*/

class PG25664CG : public DisplayCore {
    private:

        uint8_t _buffer[8192];

        uint8_t pin_dc;
        uint8_t pin_wr;
        uint8_t pin_rd;
        uint8_t pin_cs;
        uint8_t pin_res;

        uint8_t pin_d0;
        uint8_t pin_d1;
        uint8_t pin_d2;
        uint8_t pin_d3;
        uint8_t pin_d4;
        uint8_t pin_d5;
        uint8_t pin_d6;
        uint8_t pin_d7;

        void setAddressWindow(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye);

        void update();
        virtual void command(uint8_t);
        virtual void data(uint8_t);

    public:
        int _buffered;

        PG25664CG(uint8_t dc, uint8_t wr, uint8_t rd, uint8_t cs, uint8_t reset,
                uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) :
                pin_dc(dc), pin_wr(wr), pin_rd(rd), pin_cs(cs), pin_res(reset),
                pin_d0(d0), pin_d1(d1), pin_d2(d2), pin_d3(d3),
                pin_d4(d4), pin_d5(d5), pin_d6(d6), pin_d7(d7),
                _buffered(0) {}

        PG25664CG() : _buffered(0) {}

        void startDisplay();

        virtual void initializeDevice() {
            pinMode(pin_dc, OUTPUT);
            pinMode(pin_wr, OUTPUT);
            pinMode(pin_rd, OUTPUT);
            pinMode(pin_cs, OUTPUT);
            pinMode(pin_res, OUTPUT);
            pinMode(pin_d0, OUTPUT);
            pinMode(pin_d1, OUTPUT);
            pinMode(pin_d2, OUTPUT);
            pinMode(pin_d3, OUTPUT);
            pinMode(pin_d4, OUTPUT);
            pinMode(pin_d5, OUTPUT);
            pinMode(pin_d6, OUTPUT);
            pinMode(pin_d7, OUTPUT);
            digitalWrite(pin_dc, HIGH);
            digitalWrite(pin_wr, HIGH);
            digitalWrite(pin_rd, HIGH);
            digitalWrite(pin_cs, LOW);
            digitalWrite(pin_res, HIGH);
            delay(100);
            digitalWrite(pin_res, LOW);
            delay(100);
            digitalWrite(pin_res, HIGH);
            delay(100);

            startDisplay();
        }
        void displayOn();
        void displayOff();
        void setPixel(int16_t x, int16_t y, uint16_t c);
        void fillScreen(uint16_t c);

        void setRotation(uint8_t r) {}
        void invertDisplay(boolean i) {}

        void startBuffer();
        void endBuffer();

        uint16_t getWidth() { return 256; }
        uint16_t getHeight() { return 64; }

};

class PG25664CG_PORTB : public PG25664CG {
    private:

        uint8_t pin_dc;
        uint8_t pin_wr;
        uint8_t pin_rd;
        uint8_t pin_cs;
        uint8_t pin_res;
        uint8_t pin_data;

        void command(uint8_t);
        void data(uint8_t);
         
    public:
        PG25664CG_PORTB(uint8_t dc, uint8_t wr, uint8_t rd, uint8_t cs, uint8_t res, uint8_t doff) : pin_dc(dc), pin_wr(wr), pin_rd(rd), pin_cs(cs), pin_res(res), pin_data(doff) {}

        void initializeDevice() {
            TRISBCLR = 1<<pin_dc;
            TRISBCLR = 1<<pin_wr;
            TRISBCLR = 1<<pin_rd;
            TRISBCLR = 1<<pin_cs;
            TRISBCLR = 1<<pin_res;
            TRISBCLR = 0xFF<<pin_data;

            LATBSET = 1<<pin_dc;
            LATBSET = 1<<pin_wr;
            LATBSET = 1<<pin_rd;
            LATBCLR = 1<<pin_cs;
            LATBSET = 1<<pin_res;
    
            delay(100);
            LATBCLR = 1<<pin_res;
            delay(100);
            LATBSET = 1<<pin_res;
            delay(100);
            startDisplay();
        }
};

class PG25664CG_PMP : public PG25664CG {
    private:

        uint8_t pin_res;

        void command(uint8_t);
        void data(uint8_t);
         
    public:
        PG25664CG_PMP(uint8_t res) : pin_res(res) {}

        void initializeDevice() {
            PMCONbits.ON = 0;
            asm volatile("nop");

            PMCONbits.PTWREN = 1;
            PMCONbits.PTRDEN = 1;
            PMCONbits.CSF = 0b01; // Enable CS2

            PMAEN = 0x8001; // Enable PMA0 pin for DC pin and CS2 as CS

            PMMODEbits.MODE16 = 0;
            PMMODEbits.MODE = 0b10;
            PMMODEbits.WAITB = 0;
            PMMODEbits.WAITM = 0;
            PMMODEbits.WAITE = 0;

            PMADDR = 0x8000; // Set current address to 0, CS2 Active

            PMCONbits.ON = 1;

            pinMode(pin_res, OUTPUT);

            digitalWrite(pin_res, HIGH);
            delay(100);
            digitalWrite(pin_res, LOW);
            delay(100);
            digitalWrite(pin_res, HIGH);
            delay(100);
            startDisplay();
        }
};

#endif

