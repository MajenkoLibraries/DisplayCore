#include <DisplayCore.h>
#include <stdarg.h>

/*! \name Text handing functions
 *  These are functions used for dealing with text and printing of strings to the screen.
 */

/*! Calculate the width of a string
 *  ===============================
 *  The total width of a string of characters is calculated by examining the width of each
 *  character using the current font in turn and accumulating the total width.
 *
 *  Example:
 *
 *      int width = tft.stringWidth("The quick brown fox jumped over the lazy dog");
 */
int DisplayCore::stringWidth(const char *text) {
    int w = 0;
    if (font == NULL) {
        return 1;
    }
    FontHeader *header = (FontHeader *)font;

    for (const char *t = text; *t; t++) {
        uint8_t c = *t;
        if (c < header->startGlyph) {
            if (c >= 'A' && c <= 'Z') {
                c += ('a' - 'A');
            }
        }
        if (c > header->endGlyph) {
            if (c >= 'a' && c <= 'z') {
                c -= ('a' - 'A');
            }
        }
        if (c >= header->startGlyph && c <= header->endGlyph) {
            uint8_t co = c - header->startGlyph;
            uint32_t charstart = (co * ((header->linesPerCharacter * header->bytesPerLine) + 1)) + sizeof(FontHeader); // Start of character data
            uint8_t charwidth = font[charstart++];
            w += charwidth;
        }
    }
    return w;
}
        
/*! Calculate the height of a string
 *  ================================
 *  As fonts are all fixed height, this just returns the height of the
 *  currently selected font in pixels.
 *
 *  Example:
 *
 *      int height = stringHeight("The quick brown fox jumped over the lazy dog");
 */
int DisplayCore::stringHeight(const char *text) {
    if (font == NULL) {
        return 0;
    }
    FontHeader *header = (FontHeader *)font;

    return header->linesPerCharacter;
}
        

#if ARDUINO >= 100
size_t DisplayCore::write(const uint8_t *buffer, size_t size) {
    startBuffer();
    for (size_t i = 0; i < size; i++) {
        write(buffer[i]);
    }
    endBuffer();
    return size;
}
#else
void DisplayCore::write(const uint8_t *buffer, size_t size) {
    startBuffer();
    for (size_t i = 0; i < size; i++) {
        write(buffer[i]);
    }
    endBuffer();
}
#endif

/*! Write a character to the screen
 *  ===============================
 *  This writes a single character to the screen at the current cursor position.  It is used by (among other
 *  things) the print routines for rendering strings.
 *
 *  Example:
 *
 *      tft.write('Q');
 */
#if ARDUINO >= 100
size_t DisplayCore::write(uint8_t c) {
    if (font == NULL) {
        return 0;
    }
#else
void DisplayCore::write(uint8_t c) {
    if (font == NULL) {
        return;
    }
#endif
    FontHeader *header = (FontHeader *)font;

    if (c == '\n') {
        cursor_y += header->linesPerCharacter;
        cursor_x = 0;
    } else if (c == '\r') {
        // skip em
    } else {
        if (c < header->startGlyph) {
            if (c >= 'A' && c <= 'Z') {
                c += ('a' - 'A');
            }
        }
        if (c > header->endGlyph) {
            if (c >= 'a' && c <= 'z') {
                c -= ('a' - 'A');
            }
        }
        if (c >= header->startGlyph && c <= header->endGlyph) {
            uint8_t co = c - header->startGlyph;
            uint32_t charstart = (co * ((header->linesPerCharacter * header->bytesPerLine) + 1)) + sizeof(FontHeader); // Start of character data
            uint8_t charwidth = font[charstart++];
            if (wrap && (cursor_x > (getWidth() - charwidth))) {
                cursor_y += header->linesPerCharacter;
                cursor_x = 0;
            }
            cursor_x += drawChar(cursor_x, cursor_y, c, textcolor, textbgcolor);
        }
    }
#if ARDUINO >= 100
    return 1;
#endif
}

/*! Draw a character
 *  ================
 *  This is the heart of the text handling.  It takes the current font, locates the right character (c)
 *  data, and renders it to the screen at the specified (x,y) location.  It is drawn in colour (color), and
 *  the background is filled in (bg).  If (bg) and (color) are equal then the background pixels are
 *  skipped.
 *
 *  Example:
 *
 *      tft.drawChar(30, 30, 'Q', Color::Red, Color::Blue);
 */
int DisplayCore::drawChar(int x, int y, unsigned char c, color_t color, color_t bg) {

    if (font == NULL) {
        return 0;
    }

    FontHeader *header = (FontHeader *)font;

    if (c < header->startGlyph || c > header->endGlyph) {
        return 0;
    }

    startBuffer();

    c = c - header->startGlyph;

    // Start of this character's data is the character number multiplied by the
    // number of lines in a character (plus one for the character width) multiplied
    // by the number of bytes in a line, and then offset by 4 for the header.
    uint32_t charstart = (c * ((header->linesPerCharacter * header->bytesPerLine) + 1)) + sizeof(FontHeader); // Start of character data
    uint8_t charwidth = font[charstart++]; // The first byte of a block is the width of the character

    uint8_t nCols = 1 << header->bitsPerPixel;
    uint32_t bitmask = nCols - 1;
    color_t cmap[nCols];

    if (bg != color) {
        for (uint8_t i = 0; i < nCols; i++) {
            cmap[i] = mix(bg, color, 255 * i / bitmask);
        }

        openWindow(x, y, charwidth, header->linesPerCharacter);

        for (int8_t lineNumber = 0; lineNumber < header->linesPerCharacter; lineNumber++ ) {
            uint8_t lineData = 0;

            int8_t bitsLeft = -1;
            uint8_t byteNumber = 0;


            for (int8_t pixelNumber = 0; pixelNumber < charwidth; pixelNumber++) {
                if (bitsLeft <= 0) {
                    bitsLeft = 8;
                    lineData = font[charstart + (lineNumber * header->bytesPerLine) + (header->bytesPerLine - byteNumber - 1)];
                    byteNumber++;
                }
                uint32_t pixelValue = lineData & bitmask;

                windowData(cmap[pixelValue]);
    
                lineData >>= header->bitsPerPixel;
                bitsLeft -= header->bitsPerPixel;
            }
        }
        closeWindow();
    } else {

        for (int8_t lineNumber = 0; lineNumber < header->linesPerCharacter; lineNumber++ ) {
            uint8_t lineData = 0;

            int8_t bitsLeft = -1;
            uint8_t byteNumber = 0;


            for (int8_t pixelNumber = 0; pixelNumber < charwidth; pixelNumber++) {
                if (bitsLeft <= 0) {
                    bitsLeft = 8;
                    lineData = font[charstart + (lineNumber * header->bytesPerLine) + (header->bytesPerLine - byteNumber - 1)];
                    byteNumber++;
                }
                uint32_t pixelValue = lineData & bitmask;

                // If we have some kind of foreground colour...
                if (pixelValue > 0) {
                    // If it is at full opacity...
                    if (pixelValue == bitmask) {
                        setPixel(x + pixelNumber, y + lineNumber, color);
                    // Otherwise mix or fade the colour...
                    } else {
                        color_t bgc = colorAt(x+pixelNumber, y+lineNumber);
                        setPixel(x + pixelNumber, y + lineNumber, mix(bgc, color, 255 * pixelValue / bitmask));
                    }
                }
                lineData >>= header->bitsPerPixel;
                bitsLeft -= header->bitsPerPixel;
            }
        }
    }
    endBuffer();
    return charwidth;
}

/*! Set the text cursor
 *  ===================
 *  All future printing will happen from the pixel (x,y).
 *
 *  Example:
 *
 *      tft.setCursor(0, 100);
 */
void DisplayCore::setCursor(int x, int y) {
    cursor_x = x;
    cursor_y = y;
}

/*! Set the text X cursor
 *  =====================
 *  All future printing will happen from the X pixel (x).
 *
 *  Example:
 *
 *      tft.setCursorX(100);
 */
void DisplayCore::setCursorX(int x) {
    cursor_x = x;
}

/*! Set the text Y cursor
 *  =====================
 *  All future printing will happen from the Y pixel (y).
 *
 *  Example:
 *
 *      tft.setCursorY(100);
 */
void DisplayCore::setCursorY(int y) {
    cursor_y = y;
}

/*! Get X Cursor 
 *  ============
 *  Returns the current X position of the text cursor.
 *
 *  Example:
 *
 *      int x = tft.getCursorX();
 */
int DisplayCore::getCursorX() {
    return cursor_x;
}

/*! Get Y Cursor 
 *  ============
 *  Returns the current Y position of the text cursor.
 *
 *  Example:
 *
 *      int y = tft.getCursorY();
 */
int DisplayCore::getCursorY() {
    return cursor_y;
}

/*! Get Text Cursor 
 *  ============
 *  Returns the ether the current X or Y position of the text cursor.  A parameter of `true`
 *  requests the X coordinate, otherwise the Y coordinate is returned.
 *
 *  Example:
 *
 *      int x = tft.getCursor(true);
 *      int y = tft.getCursor(false);
 */
int DisplayCore::getCursor(boolean x) {
    if( x )
        return cursor_x;
    return cursor_y;
}

/*! Set the text foreground colour
 *  ==============================
 *  Sets the foreground colour of all future printing to (c).
 *
 *  Example:
 *
 *      tft.setTextColor(Color::Magenta);
 */
void DisplayCore::setTextColor(color_t c) {
    textcolor = c;
}

/*! Sets both foreground and background colour
 *  ==========================================
 *  Sets both the foreground and the background colours of all
 *  future printing.  If the foreground and background colours match
 *  the background will be transparent.
 *
 *  Example:
 *
 *      tft.setTextColor(Color::Red, Color::Blue);
 */
void DisplayCore::setTextColor(color_t fg, color_t bg) {
   textcolor = fg;
   textbgcolor = bg;
    bgColor = bg;
}

/*! Invert the text colours
 *  =======================
 *  The foreground becomes the background, and the background becomes the foreground.
 *
 *  Example:
 *
 *      tft.invertTextColor();
 */
void DisplayCore::invertTextColor( ){
	setTextColor( textbgcolor, textcolor );
}

/*! Enable or disable text wrapping
 *  ===============================
 *  With text wrapping enabled, when text reaches the right-hand edge of the
 *  screen it wraps around back to the left on the next line down.  This function
 *  alows you to enable (true) or disable (false) this functionality.  By default
 *  text wrapping is enabled.
 *
 *  Example:
 * 
 *      tft.setTextWrap(false);
 */
void DisplayCore::setTextWrap(boolean w) {
  wrap = w;
}

/*! Set the current font
 *  ====================
 *  The current font is set to the font provided.  A font is a byte array of data with
 *  metric information embedded in it.
 *
 *  Example:
 * 
 *      tft.setFont(Fonts::Ubuntu12);
 */
void DisplayCore::setFont(const uint8_t *f) {
    font = f;
}

/*! Get the current foreground colour
 *  =================================
 *  Returns the currently selected foreground colour.
 *
 *  Example:
 *
 *      unsigned int color = tft.getTextColor();
 */
color_t DisplayCore::getTextColor() {
    return textcolor;
}


