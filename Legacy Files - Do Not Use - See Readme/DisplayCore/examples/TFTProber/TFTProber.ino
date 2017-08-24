/*
 * Copyright (c) 2016, Majenko Technologies
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 * 
 * * Neither the name of Majenko Technologies nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*  TFT Screen ID Prober
 *  
 *  This program will attempt to identify the connected TFT screen by searching
 *  for a unique ID code in the registers. Not all TFT or OLED screens provide
 *  such an ID, and many SPI TFT screens don't provide a MISO connection to
 *  read the ID even if one is available.
 *  
 *  Instructions:
 *  
 *  1. Wire up the TFT screen as you see fit (or plug it in if it's a shield).
 *  2. Select the correct interface type in the #defines below.
 *  3. Configure the pins in the correct pin definition section for your chosen
 *     interface.
 *  4. Program it and open the serial terminal (115200 baud).
 *  
 *  The TFT screen should be displayed. If it can't work out what the screen is
 *  it will provide a complete register dump. This may be used to extend the
 *  list of screens the program recognises. Send that dump, along with details
 *  of the screen you have, to Majenko Technologies (through a Github issue at
 *  https://github.com/MajenkoLibraries/DisplayCore/issues) to see if support
 *  for your screen can be added.
 */

// Uncomment ONE of these definitions to select the right interface.
// Then set the pins in the right section below.

// SPI interface with RS(DC), CS and RESET
//#define USES_SPI

// 8-bit parallel interface: D0-7, RS, CS, RD, WR and RESET
#define USES_8BIT

// 16-bit parallel interface: D0-15, RS, CS, RD, WR and RESET
//#define USES_16BIT


// Configure these pins if you selected SPI above.

#if defined(USES_SPI)
// RS is sometimes known as DC
#define RS 7
#define CS 10
#define RESET 9
#define DSPIPORT DSPI0
#endif

// Configure these pins if you selected 8 bit above.

#if defined(USES_8BIT)
#define RS A2
#define WR A1
#define RD A0
#define CS A3
#define RESET A4

#define D0 8
#define D1 9
#define D2 2
#define D3 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7
#endif

// Configure these pins if you selected 16 bit above.

#if defined(USES_16BIT)
#define RS A0
#define WR A1
#define RD A2
#define CS A3
#define RESET A4

#define D0 26
#define D1 27
#define D2 28
#define D3 29
#define D4 30
#define D5 31
#define D6 32
#define D7 33
#define D8 34
#define D9 35
#define D10 36
#define D11 37
#define D12 38
#define D13 39
#define D14 40
#define D15 41
#endif

// Now the program begins. You shouldn't need to modify anything below here.

#if defined(USES_SPI)
#include <DSPI.h>
DSPIPORT spi;
#endif


struct displaycode {
    uint32_t reg;
    uint32_t id;
    uint32_t imask;
    uint32_t extra0;
    uint32_t emask0;
    uint32_t extra1;
    uint32_t emask1;
    uint32_t extra2;
    uint32_t emask2;
    const char *name;
};

// This is the list of codes for the screens.  It takes the form of a register
// number to probe followed by 4 32-bit data values. Each data value has an
// associated mask which indicates the bits within the data value that actually
// have any meaning.  Finally is the name of the display controller chip.

const struct displaycode ids[] = {
    {0x00,  0x01540000, 0xFFFF0000, 
            0x00000000, 0x00000000, 
            0x00000000, 0x00000000,
            0x00000000, 0x00000000,
            "P6D0154"},
            
    {0x04,  0x93250000, 0xFFFF0000, 
            0x00000000, 0x00000000, 
            0x00000000, 0x00000000, 
            0x00000000, 0x00000000, 
            "ILI9325"},

    {0x00,  0x01006400, 0xFF00FF00, 
            0x00000000, 0x00000000, 
            0x00000000, 0x00000000, 
            0x00000000, 0x00000000, 
            "P6D0164"},
    
    // TODO: Get the code for this screen (mine is write-only)
    {0x00,  0x89898989, 0xFFFFFFFF, 
            0x00000000, 0x00000000, 
            0x00000000, 0x00000000, 
            0x00000000, 0x00000000, 
           "SSD1289"},

    // TODO: Get the code for this screen (mine is broken)
    {0xA1,  0x12345678, 0xFFFFFFFF, 
            0x00000000, 0x00000000, 
            0x00000000, 0x00000000, 
            0x00000000, 0x00000000, 
            "SSD1963"},
            
    {0xBF,  0x00000002, 0x0000FFFF, 
            0x00040094, 0xFFFFFFFF, 
            0x00810000, 0xFFFF0000, 
            0x00000000, 0x00000000, 
            "ILI9481"},

    {0x00,  0x47000000, 0xFF000000,
            0x00000000, 0x00000000,
            0x00000000, 0x00000000,
            0x00000000, 0x00000000,
            "HX8347D"},
    {0x04,  0x00009302, 0x0000FFFF,
            0x00000000, 0x00000000,
            0x00000000, 0x00000000,
            0x00000000, 0x00000000,
            "ILI9341"},

    {0, 0, 0, 0, 0, 0}
};

// Read four 32-bit values from a register
uint32_t readRegister(uint8_t r, uint32_t &extra0, uint32_t &extra1, uint32_t &extra2) {
    digitalWrite(RS, LOW);
    digitalWrite(CS, LOW);
    writeByte(r);
    digitalWrite(RS, HIGH);
    uint32_t val = readWord();
    extra0 = readWord();
    extra1 = readWord();
    extra2 = readWord();
    digitalWrite(CS, HIGH);
    return val;
}

// Attempt to find the ID code in the list.
int readIDCode() {
    Serial.print("Reading ID code... ");
    for (int i = 0; ids[i].name; i++) {
        uint32_t extra0;
        uint32_t extra1;
        uint32_t extra2;
        
        uint32_t id = readRegister(ids[i].reg, extra0, extra1, extra2);
        
        id &= ids[i].imask;
        extra0 &= ids[i].emask0;
        extra1 &= ids[i].emask1;
        extra2 &= ids[i].emask2;
        if (id == ids[i].id && extra0 == ids[i].extra0 && extra1 == ids[i].extra1 && extra2 == ids[i].extra2) {
            Serial.println("ok.");
            return i;
        }
    }
    Serial.println("error.");
    return -1;
}

// Perform a hard reset.
void resetScreen() {
    delay(100);
    digitalWrite(RESET, LOW);
    delay(100);
    digitalWrite(RESET, HIGH);
    delay(100);
}

void setup() {
    Serial.begin(115200);
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println("==================================================");
    Serial.println("     TFT Screen Prober (8 bit parallel) V1.0      ");
    Serial.println("               Majenko Technologies               ");
    Serial.println("==================================================");
    Serial.println();
    Serial.print("Configuring interface...");
    initInterface();
    Serial.println("ok.");
    Serial.print("Resetting screen...");
    resetScreen();
    Serial.println("ok.");
    int idcode = readIDCode();

    if (idcode >= 0) {
        Serial.print("Screen is: ");
        Serial.println(ids[idcode].name);
    } else {
        Serial.println("I cannot identify this screen. Please send details of the");
        Serial.println("screen to Majenko Technologies.");
        Serial.println();
        Serial.println("Register dump follows:");
        Serial.println();
        for (int i = 0; i < 256; i++) {
            uint32_t extra0;
            uint32_t extra1;
            uint32_t extra2;
            uint32_t id = readRegister(i, extra0, extra1, extra2);
            Serial.printf("0x%02X = 0x%08X 0x%08X 0x%08X 0x%08X", i, id, extra0, extra1, extra2);
            Serial.println();
        }
    }
}

// Nothing happens in loop. Press reset to run the code again.
void loop() {    
}





// Read and write functions for the different interface types.

#if defined(USES_8BIT) 
void writeByte(uint32_t c) {
    pinMode(D0, OUTPUT);
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);
    pinMode(D4, OUTPUT);
    pinMode(D5, OUTPUT);
    pinMode(D6, OUTPUT);
    pinMode(D7, OUTPUT);

    digitalWrite(D0, c & 0x01);
    digitalWrite(D1, c & 0x02);
    digitalWrite(D2, c & 0x04);
    digitalWrite(D3, c & 0x08);
    digitalWrite(D4, c & 0x10);
    digitalWrite(D5, c & 0x20);
    digitalWrite(D6, c & 0x40);
    digitalWrite(D7, c & 0x80);
    digitalWrite(WR, LOW);
    digitalWrite(WR, HIGH);
}

uint32_t readByte() {
    uint8_t v = 0;
    pinMode(D0, INPUT);
    pinMode(D1, INPUT);
    pinMode(D2, INPUT);
    pinMode(D3, INPUT);
    pinMode(D4, INPUT);
    pinMode(D5, INPUT);
    pinMode(D6, INPUT);
    pinMode(D7, INPUT);
    digitalWrite(RD, LOW);
    v |= digitalRead(D0) ? 0x01 : 0x00;
    v |= digitalRead(D1) ? 0x02 : 0x00;
    v |= digitalRead(D2) ? 0x04 : 0x00;
    v |= digitalRead(D3) ? 0x08 : 0x00;
    v |= digitalRead(D4) ? 0x10 : 0x00;
    v |= digitalRead(D5) ? 0x20 : 0x00;
    v |= digitalRead(D6) ? 0x40 : 0x00;
    v |= digitalRead(D7) ? 0x80 : 0x00;
    digitalWrite(RD, HIGH);
    return v;
}

uint32_t readWord() {
    uint8_t b3 = readByte();
    uint8_t b2 = readByte();
    uint8_t b1 = readByte();
    uint8_t b0 = readByte();
    return (b3 << 24) | (b2 << 16) | (b1 << 8) | b0;
}

void initInterface() {
    pinMode(RS, OUTPUT);
    pinMode(WR, OUTPUT);
    pinMode(CS, OUTPUT);
    pinMode(RD, OUTPUT);
    pinMode(RESET, OUTPUT);
    digitalWrite(RS, HIGH);
    digitalWrite(WR, HIGH);
    digitalWrite(RD, HIGH);
    digitalWrite(CS, HIGH);
    digitalWrite(RESET, HIGH);
}
#endif

#if defined(USES_16BIT) 
void writeByte(uint32_t c) {
    pinMode(D0, OUTPUT);
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);
    pinMode(D4, OUTPUT);
    pinMode(D5, OUTPUT);
    pinMode(D6, OUTPUT);
    pinMode(D7, OUTPUT);
    pinMode(D8, OUTPUT);
    pinMode(D9, OUTPUT);
    pinMode(D10, OUTPUT);
    pinMode(D11, OUTPUT);
    pinMode(D12, OUTPUT);
    pinMode(D13, OUTPUT);
    pinMode(D14, OUTPUT);
    pinMode(D15, OUTPUT);

    digitalWrite(D0, c & 0x0001);
    digitalWrite(D1, c & 0x0002);
    digitalWrite(D2, c & 0x0004);
    digitalWrite(D3, c & 0x0008);
    digitalWrite(D4, c & 0x0010);
    digitalWrite(D5, c & 0x0020);
    digitalWrite(D6, c & 0x0040);
    digitalWrite(D7, c & 0x0080);
    digitalWrite(D8, c & 0x0100);
    digitalWrite(D9, c & 0x0200);
    digitalWrite(D10, c & 0x0400);
    digitalWrite(D11, c & 0x0800);
    digitalWrite(D12, c & 0x1000);
    digitalWrite(D13, c & 0x2000);
    digitalWrite(D14, c & 0x4000);
    digitalWrite(D15, c & 0x8000);
    delay(1);
    digitalWrite(WR, LOW);
    delay(1);
    digitalWrite(WR, HIGH);
}

uint32_t readByte() {
    uint16_t v = 0;
    pinMode(D0, INPUT);
    pinMode(D1, INPUT);
    pinMode(D2, INPUT);
    pinMode(D3, INPUT);
    pinMode(D4, INPUT);
    pinMode(D5, INPUT);
    pinMode(D6, INPUT);
    pinMode(D7, INPUT);
    pinMode(D8, INPUT);
    pinMode(D9, INPUT);
    pinMode(D10, INPUT);
    pinMode(D11, INPUT);
    pinMode(D12, INPUT);
    pinMode(D13, INPUT);
    pinMode(D14, INPUT);
    pinMode(D15, INPUT);
    digitalWrite(RD, LOW);
    delay(1);
    v |= digitalRead(D0) ? 0x0001 : 0x0000;
    v |= digitalRead(D1) ? 0x0002 : 0x0000;
    v |= digitalRead(D2) ? 0x0004 : 0x0000;
    v |= digitalRead(D3) ? 0x0008 : 0x0000;
    v |= digitalRead(D4) ? 0x0010 : 0x0000;
    v |= digitalRead(D5) ? 0x0020 : 0x0000;
    v |= digitalRead(D6) ? 0x0040 : 0x0000;
    v |= digitalRead(D7) ? 0x0080 : 0x0000;
    v |= digitalRead(D8) ? 0x0100 : 0x0000;
    v |= digitalRead(D9) ? 0x0200 : 0x0000;
    v |= digitalRead(D10) ? 0x0400 : 0x0000;
    v |= digitalRead(D11) ? 0x0800 : 0x0000;
    v |= digitalRead(D12) ? 0x1000 : 0x0000;
    v |= digitalRead(D13) ? 0x2000 : 0x0000;
    v |= digitalRead(D14) ? 0x4000 : 0x0000;
    v |= digitalRead(D15) ? 0x8000 : 0x0000;
    digitalWrite(RD, HIGH);
    return v;
}

uint32_t readWord() {
    uint16_t b1 = readByte();
    uint16_t b0 = readByte();
    return (b1 << 16) | b0;
}

void initInterface() {
    pinMode(RS, OUTPUT);
    pinMode(WR, OUTPUT);
    pinMode(CS, OUTPUT);
    pinMode(RD, OUTPUT);
    pinMode(RESET, OUTPUT);
    digitalWrite(RS, HIGH);
    digitalWrite(WR, HIGH);
    digitalWrite(RD, HIGH);
    digitalWrite(CS, HIGH);
    digitalWrite(RESET, HIGH);
}
#endif


#if defined(USES_SPI) 
void writeByte(uint32_t c) {
    spi.transfer(c);
}

uint32_t readByte() {
    return spi.transfer((uint8_t)0x00);
}

uint32_t readWord() {
    uint8_t b3 = readByte();
    uint8_t b2 = readByte();
    uint8_t b1 = readByte();
    uint8_t b0 = readByte();
    return (b3 << 24) | (b2 << 16) | (b1 << 8) | b0;
}

void initInterface() {
    spi.begin();
    spi.setSpeed(1000000UL);
    pinMode(RS, OUTPUT);
    pinMode(CS, OUTPUT);
    pinMode(RESET, OUTPUT);
    digitalWrite(RS, HIGH);
    digitalWrite(CS, HIGH);
    digitalWrite(RESET, HIGH);
}
#endif
