#include <DisplayCore.h>
#include <stdarg.h>

void DisplayCore::drawBezier(
    int x0, int y0,
    int x1, int y1,
    int x2, int y2,
    int x3, int y3,
    int resolution,
    color_t color
) {
    startBuffer();

    boolean first = true;
    double points = 1.0/(double)resolution;
    double t = 0.0, sx = 0, sy = 0;
    double ex, ey;


    for (t = 0.0; t < 1.0; t += points)
    {
        ex = pow (1-t, 3) * x0 + 3 * t * pow (1-t, 2) * x1 +
                   3 * pow (t, 2) * (1-t) * x2 + pow (t, 3) * x3;
 
        ey = pow (1-t, 3) * y0 + 3 * t * pow (1-t, 2) * y1 +
                   3 * pow (t, 2) * (1-t) * y2 + pow (t, 3) * y3;

        if (!first) {
            drawLine(sx, sy, ex, ey, color);
        }
        first = false;
        sx = ex;
        sy = ey;
    }
    drawLine(sx, sy, x3, y3, color);
    endBuffer();
}

void DisplayCore::fillBezier(
    int x0, int y0,
    int x1, int y1,
    int x2, int y2,
    int x3, int y3,
    int resolution,
    color_t color
) {

    startBuffer();

    boolean first = true;
    double points = 1.0/(double)resolution;
    double t = 0.0, sx = 0, sy = 0;
    double ex, ey;


    for (t = 0.0; t < 1.0; t += points)
    {
        ex = pow (1-t, 3) * x0 + 3 * t * pow (1-t, 2) * x1 +
                   3 * pow (t, 2) * (1-t) * x2 + pow (t, 3) * x3;
 
        ey = pow (1-t, 3) * y0 + 3 * t * pow (1-t, 2) * y1 +
                   3 * pow (t, 2) * (1-t) * y2 + pow (t, 3) * y3;

        if (!first) {
            fillTriangle(sx, sy, ex, ey, x0, y0, color);
        }
        first = false;
        sx = ex;
        sy = ey;
    }
    fillTriangle(x0, y0, sx, sy, x3, y3, color);
    endBuffer();
}

