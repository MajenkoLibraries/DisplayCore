#include <DisplayCore.h>
#include <stdarg.h>

#ifndef max
#define max(X,Y) ((X) > (Y) ? (X) : (Y))
#endif

/*! Utility function to convert a 24-bit RGB value into a 16-bit RGB value. */
color_t rgb(uint32_t c) {
    uint8_t r = c >> 16;
    uint8_t g = c >> 8;
    uint8_t b = c;

    r = r >> 3;
    g = g >> 2;
    b = b >> 3;
    return ((r << 11) | (g << 5) | b);
}

/*! Utility function to convert three component colour values (R, G, B) into a 16-bit RGB value.*/
color_t rgb(uint8_t r, uint8_t g, uint8_t b) {
    r = r >> 3;
    g = g >> 2;
    b = b >> 3;
    return ((r << 11) | (g << 5) | b);
}


/*! Display a fatal error
 *  =====================
 *  Used internally by various functions and libraries to display
 *  a fatal error message.  This is an error that cannot be recovered
 *  from, so the program stops here.
 *
 *  Example:
 *
 *      tft.fatalError("MEMORY ERROR", "Unable to allocate space for objects");
 */
void DisplayCore::fatalError(const char *title, const char *message) {
    int width = getWidth();
    int height = getHeight();
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if ((x + (y & 1)) & 1) {
                setPixel(x, y, Color::Black);
            }
        }
    }
    setFont(Fonts::Default);
    int sx = 1;
    int swidth = stringWidth((char *)message);
    int twidth = stringWidth((char *)title);
    int mwidth = max(swidth, twidth);
    while (mwidth < width) {
        sx++;
        swidth = stringWidth((char *)message);
        twidth = stringWidth((char *)title);
        mwidth = max(swidth, twidth);
    }
    sx--;
    swidth = stringWidth((char *)message);
    int sheight = stringHeight((char *)message);
    twidth = stringWidth((char *)title);
    mwidth = max(swidth, twidth);

    int strw2 = swidth / 2;
    int ttlw2 = twidth / 2;
    int maxw2 = mwidth / 2;
    int scrw2 = width / 2;
    int scrh2 = height / 2;
    fillRoundRect(scrw2 - maxw2 - 14, scrh2 - sheight - 14, mwidth + 28, sheight * 2 + 28, 12, Color::Black);
    fillRoundRect(scrw2 - maxw2 - 10, scrh2 - sheight - 10, mwidth + 20, sheight * 2 + 20, 10, Color::Red);
    drawRoundRect(scrw2 - maxw2 - 12, scrh2 - sheight - 12, mwidth + 24, sheight * 2 + 24, 12, Color::Red);

    setTextColor(Color::Black, Color::Red);
    setCursor(scrw2 - ttlw2, scrh2 - sheight - 1);
    print(title);
    setTextColor(Color::Black, Color::Red);
    setCursor(scrw2 - strw2, scrh2 + 1);
    print(message);

    while(1) {
        delay(500);
        drawRoundRect(scrw2 - maxw2 - 12, scrh2 - sheight - 12, mwidth + 24, sheight * 2 + 24, 12, Color::Black);
        drawRoundRect(scrw2 - maxw2 - 14, scrh2 - sheight - 14, mwidth + 28, sheight * 2 + 28, 12, Color::Red);
        delay(500);
        drawRoundRect(scrw2 - maxw2 - 12, scrh2 - sheight - 12, mwidth + 24, sheight * 2 + 24, 12, Color::Red);
        drawRoundRect(scrw2 - maxw2 - 14, scrh2 - sheight - 14, mwidth + 28, sheight * 2 + 28, 12, Color::Black);
    }
}


