/*
 * Copyright (c) 2014, Majenko Technologies
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

/*
 * High Speed Wave
 * 
 * This requires an audio input to A0.  It should have a Vcc/2 offset imposed on it and be decoupled with a capacitor.
 * 
 * For example:
 * Two resistors (10K) making a voltage divider between 3.3V and GND connected to A0, and the audio signal connected
 * to A0 via a 22uF capacitor.
 */

#include <Picadillo.h>
#include <Topaz.h>

// Configure the display
Picadillo tft;

void printCentered(uint16_t pos, char *data) {
	uint16_t w = tft.stringWidth(data);
	tft.setCursor((tft.getWidth() / 2) - (w / 2), pos);
	tft.print(data);
}

void setup() {
	tft.initializeDevice();
    tft.setBacklight(255);
	tft.setRotation(0);
	tft.fillScreen(Color::Black);
	tft.setFont(Fonts::Topaz);
	tft.setTextColor(Color::White, Color::Black);	
	printCentered(50, "High Speed Wave");
	printCentered(70, "Audio Visualisation");
	configureADC(192000);
	AD1CON1bits.ON = 1;
}

int32_t data[320];

void loop() {
    int32_t window[320];

	while (AD1CON1bits.ON == 1);
    for (int i = 0; i < 320; i++) {
    	window[i] = data[i];
    }
	AD1CON1bits.ON = 1;

	tft.openWindow(0, 128, 320, 255);
	for (int y = 0; y < 255; y++) {
		for (int x = 0; x < 320; x++) {
			if (y == 128) {
				tft.windowData(Color::Green);				
			} else if (y < 128) {
				if (window[x] > 128-y) {
					tft.windowData(rgb((127-y)*2, 255-((127-y)*2), 0));
				} else {
					tft.windowData(rgb(0, 0, window[64+y]));
				}
			} else {
				if (window[x] > y-128) {
					tft.windowData(rgb((y-128)*2, 255-((y-128)*2), 0));					
				} else {
					tft.windowData(rgb(0, 0, window[64+y]));
				}
			}
		}
	}
	tft.closeWindow();
}


boolean configureADC(float freq) {
	uint16_t numchans = 1;
	uint16_t enabledChannels = 1;
	float f = freq * (float)numchans;
	uint32_t baseclock = F_CPU;
	uint8_t ps = 0;
	
	if (baseclock / f > 65535) {
		baseclock = F_CPU / 2;
		ps = 1;
	}

	if (baseclock / f > 65535) {
		baseclock = F_CPU / 4;
		ps = 2;
	}

	if (baseclock / f > 65535) {
		baseclock = F_CPU / 8;
		ps = 3;
	}

	if (baseclock / f > 65535) {
		baseclock = F_CPU / 16;
		ps = 4;
	}

	if (baseclock / f > 65535) {
		baseclock = F_CPU / 32;
		ps = 5;
	}

	if (baseclock / f > 65535) {
		baseclock = F_CPU / 64;
		ps = 6;
	}

	if (baseclock / f > 65535) {
		baseclock = F_CPU / 256;
		ps = 7;
	}


	AD1CON1 = 0;
	AD1CON2 = 0;
	AD1CON3 = 0;
	AD1CHS  = 0;

	AD1CON1bits.FORM = 0b101;
	AD1CON1bits.SSRC = 0b010;
	AD1CON1bits.ASAM = 1;
	AD1CON2bits.CSCNA = 1;
	AD1CON2bits.SMPI = numchans-1;
	AD1CON3bits.SAMC = 0b00111;
	AD1CON3bits.ADCS = 0b00000111;
	
	AD1PCFG = ~enabledChannels;
	AD1CSSL = enabledChannels;

	IPC6bits.AD1IP = 6;
	IFS1bits.AD1IF = 0;
	IEC1bits.AD1IE = 1;

	T3CON = 0;
	T3CONbits.TCKPS = ps;
	PR3 = baseclock / f;
	T3CONSET = 1<<15;
//	AD1CON1SET = 1<<15;
	return true;
}

extern "C" {
	#include <sys/attribs.h>
	void __ISR(_ADC_VECTOR, IPL6) _ADCInterrupt() {
		static int x = 0;
		data[x++] = abs(ADC1BUF0);
		if (x == 320) {
			x = 0;
			AD1CON1bits.ON = 0;
		}
		IFS1bits.AD1IF = 0;
	}
}

