#include <DisplayCore.h>

/*! Binary Vector Drawing Class
 *
 * The Binary Vector is a simple Vector Graphics drawing
 * class.  It takes a "program" of instructions on how to 
 * draw a shape.  The program is a simple linear list of
 * drawing operations to perform.
 */

class BinaryVector : public Image {
    private:
        const uint16_t *_program;

    public:

        // Instructions are made up of two parts.  The upper 8 bits define
        // the number of the instruction.  The lower 8 bits define the number
        // of 16-bit parameters the instruction takes.  Parameters immediately
        // follow the instruction.

        // The end of the program - needed so the system knows when it is done.
        static const uint16_t END_PROG = 0x0000;

        // Set a pixel.  Parameters: x, y, color.
        static const uint16_t SET_PIXEL = 0x0103;

        // Draw a line. Parameters: start x/y, end x/y, colour.
        static const uint16_t DRAW_LINE = 0x0205;

        // Draw a hollow box. Parameters: upper-left x/y, width/height, colour.
        static const uint16_t DRAW_BOX = 0x0305;

        // Draw a filled box. Parameters: upper-left x/y, width/height, colour.
        static const uint16_t FILL_BOX = 0x0405;

        // Bezier vector - x/y 0-3, resolution and colour.
        static const uint16_t DRAW_BEZIER = 0x050A;

        BinaryVector(const uint16_t *program) : _program(program) {}

        void draw(DisplayCore *dc, int x, int y);
        void draw(DisplayCore *dc, int x, int y, color_t) {}
        void drawTransformed(DisplayCore *dc, int x, int y, int) {}
        void drawTransformed(DisplayCore *dc, int x, int y, int, color_t) {}
};

