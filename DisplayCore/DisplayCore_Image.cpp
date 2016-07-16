#include <DisplayCore.h>
#include <stdarg.h>

/*! \name Image drawing
 *  These routines are used for drawing basic bitmap images to the screen.
 */
/*! Draw a 1-bit bitmap image
 *  =========================
 *  A 1-bit bitmap image is a byte array where each byte represents 8 contiguous pixels.
 *  The image is rendered to the screen as naturally transparent, with set bits rendered in (color)
 *  and unset bits skipped.  The image is rendered with the upper left corner at (x,y) and the image
 *  is (w,h) in size.
 *
 *  Example:
 *
 *      const byte letterA[] = {
 *          0b00000000,
 *          0b00111100,
 *          0b01000010,
 *          0b01000010,
 *          0b01111110,
 *          0b01000010,
 *          0b01000010,
 *          0b00000000};
 *      tft.drawBitmap(100, 100, letterA, 8, 8, Color::Red);
 */
void DisplayCore::drawBitmap(int x, int y, const uint8_t *bitmap, int w, int h, color_t color) {
    int i, j, byteWidth = (w + 7) / 8;

    startBuffer();
    for(j=0; j<h; j++) {
        for(i=0; i<w; i++ ) {
            if(pgm_read_byte(bitmap + j * byteWidth + i / 8) & (128 >> (i & 7))) {
                setPixel(x+i, y+j, color);
            }
        }
    }
    endBuffer();
}

/*! Draw an RGB (565) image
 *  =======================
 *  A 565 raw RGB image is rendered to the screen at (x,y).  The image data is stored
 *  as an array of 16-bit values, and is (w,h) pixels in size.
 *
 *  Example:
 *
 *    tft.drawRGB(10, 30, myImage, 16, 16);
 */
void DisplayCore::drawRGB(int x, int y, const color_t *bitmap, int w, int h) {
    startBuffer();
    int i, j;
    for (j = 0; j < h; j++) {
        for (i = 0; i < w; i++) {
            setPixel(x+i, y+j, bitmap[j * w + i]);
        }
    }
    endBuffer();
}

/*! Draw a transparent RGB (565) image
 *  ==================================
 *  A 565 raw RGB image is rendered to the screen at (x,y).  The image data is stored
 *  as an array of 16-bit values, and is (w,h) pixels in size.  Any pixels with colour
 *  (trans) are skipped.
 *
 *  Example:
 *
 *    tft.drawRGBA(10, 30, myImage, 16, 16, Color::Black);
 */
void DisplayCore::drawRGBA(int x, int y, const color_t *bitmap, int w, int h, color_t trans) {
    startBuffer();
    int i, j;
    color_t col;
    for (j = 0; j < h; j++) {
        for (i = 0; i < w; i++) {
            col = bitmap[j * w + i];
            if (col != trans) {
                setPixel(x+i, y+j, col);
            }
        }
    }
    endBuffer();
}

