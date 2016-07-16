#include <DisplayCore.h>
#include <stdarg.h>

void DisplayCore::drawPolygon3D(point3d *nodes, int numpoints, color_t color) {
    point2d p2d[numpoints];
    for (int i = 0; i < numpoints; i++) {
        p2d[i] = map3Dto2D(nodes[i]);
    }
    drawPolygon(p2d, numpoints, color);
}

void DisplayCore::fillPolygon3D(point3d *nodes, int numpoints, color_t color) {
    point2d p2d[numpoints];
    for (int i = 0; i < numpoints; i++) {
        p2d[i] = map3Dto2D(nodes[i]);
    }
    fillPolygon(p2d, numpoints, color);
}
