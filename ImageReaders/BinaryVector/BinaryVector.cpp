#include <BinaryVector.h>

void BinaryVector::draw(DisplayCore *dc, int16_t x, int16_t y) {
    const uint16_t *pc = _program;
    while (*pc != END_PROG) {
        int16_t x0, y0, x1, y1, x2, y2, x3, y3;
        uint16_t c0, c1, c2;

        uint16_t command = *pc++;

        switch(command) {
            case SET_PIXEL:
                x0 = (int16_t)*pc++;
                y0 = (int16_t)*pc++;
                c0 = *pc++;
                dc->setPixel(x0, y0, c0);
                break;
            case DRAW_LINE:
                x0 = (int16_t)*pc++;
                y0 = (int16_t)*pc++;
                x1 = (int16_t)*pc++;
                y1 = (int16_t)*pc++;
                c0 = *pc++;
                dc->drawLine(x0, y0, x1, y1, c0);
                break;
            case DRAW_BOX:
                x0 = (int16_t)*pc++;
                y0 = (int16_t)*pc++;
                x1 = (int16_t)*pc++;
                y1 = (int16_t)*pc++;
                c0 = *pc++;
                dc->drawRectangle(x0, y0, x1, y1, c0);
                break;
            case FILL_BOX:
                x0 = (int16_t)*pc++;
                y0 = (int16_t)*pc++;
                x1 = (int16_t)*pc++;
                y1 = (int16_t)*pc++;
                c0 = *pc++;
                dc->fillRectangle(x0, y0, x1, y1, c0);
                break;
            case DRAW_BEZIER:
                x0 = (int16_t)*pc++;
                y0 = (int16_t)*pc++;
                x1 = (int16_t)*pc++;
                y1 = (int16_t)*pc++;
                x2 = (int16_t)*pc++;
                y2 = (int16_t)*pc++;
                x3 = (int16_t)*pc++;
                y3 = (int16_t)*pc++;
                c0 = *pc++;
                c1 = *pc++;
                dc->bezier(x0, y0, x1, y1, x2, y2, x3, y3, c0, c1);
                break;
                
        }
    }
}

