#include <BinaryVector.h>

void BinaryVector::draw(DisplayCore *dc, int x, int y) {
    const uint16_t *pc = _program;
    while (*pc != END_PROG) {
        int x0, y0, x1, y1, x2, y2, x3, y3;
        color_t c0, c1, c2;

        uint16_t command = *pc++;

        switch(command) {
            case SET_PIXEL:
                x0 = (int)*pc++;
                y0 = (int)*pc++;
                c0 = (color_t)*pc++;
                dc->setPixel(x0, y0, c0);
                break;
            case DRAW_LINE:
                x0 = (int)*pc++;
                y0 = (int)*pc++;
                x1 = (int)*pc++;
                y1 = (int)*pc++;
                c0 = (color_t)*pc++;
                dc->drawLine(x0, y0, x1, y1, c0);
                break;
            case DRAW_BOX:
                x0 = (int)*pc++;
                y0 = (int)*pc++;
                x1 = (int)*pc++;
                y1 = (int)*pc++;
                c0 = (color_t)*pc++;
                dc->drawRectangle(x0, y0, x1, y1, c0);
                break;
            case FILL_BOX:
                x0 = (int)*pc++;
                y0 = (int)*pc++;
                x1 = (int)*pc++;
                y1 = (int)*pc++;
                c0 = (color_t)*pc++;
                dc->fillRectangle(x0, y0, x1, y1, c0);
                break;
            case DRAW_BEZIER:
                x0 = (int)*pc++;
                y0 = (int)*pc++;
                x1 = (int)*pc++;
                y1 = (int)*pc++;
                x2 = (int)*pc++;
                y2 = (int)*pc++;
                x3 = (int)*pc++;
                y3 = (int)*pc++;
                c0 = (color_t)*pc++;
                c1 = (color_t)*pc++;
                dc->drawBezier(x0, y0, x1, y1, x2, y2, x3, y3, c0, c1);
                break;
                
        }
    }
}

