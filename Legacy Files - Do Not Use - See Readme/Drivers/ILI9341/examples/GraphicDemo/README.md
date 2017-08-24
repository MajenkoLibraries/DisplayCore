Graphic Demo
============

Demonstrates some of the primitive drawing functions (lines, circles, etc)
for an ILI9341 screen (connected as SPI by default).

Wiring
------

* MOSI/MISO/SCK to the MOSI/MISO/SCK pins of your board (typically 11-13)
* CS to your selected chip select pin (pin 2 in this demo, 10 is also common)
* DC or RS (depending on how your screen describes it) to another pin of your choice
  (15 in this demo, which often equates to A1).

RESET on your screen can be either connected to RESET on your board, or tied to VCC.
