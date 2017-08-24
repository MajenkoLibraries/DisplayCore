#include <DisplayCore.h>
#include <stdarg.h>

void DisplayCore::drawPolygon(point2d *nodes, int numpoints, color_t color) {
    for (int i = 1; i < numpoints; i++) {
        drawLine(nodes[i-1].x, nodes[i-1].y, nodes[i].x, nodes[i].y, color);
    }
    drawLine(nodes[0].x, nodes[0].y, nodes[numpoints-1].x, nodes[numpoints-1].y, color);
}


void DisplayCore::fillPolygon(point2d *nodes, int numpoints, color_t color) {
    int i;
    int nodeX[20];
    int nodeCount;

    int startY = getHeight();
    int endY = 0;

    for (i = 0; i < numpoints; i++) {
        if (nodes[i].y < startY) startY = nodes[i].y;
        if (nodes[i].y > endY) endY = nodes[i].y;
    }

    for (int pixelY = startY; pixelY < endY; pixelY++) {
        int j = numpoints - 1;
        nodeCount=0; 
        for (i = 0; i < numpoints; i++) {
            if ((nodes[i].y < pixelY && nodes[j].y >= pixelY) || (nodes[j].y < pixelY && nodes[i].y >= pixelY)) {
                nodeX[nodeCount++] = nodes[i].x + (pixelY - nodes[i].y) / (nodes[j].y - nodes[i].y) * (nodes[j].x - nodes[i].x);
            }
            j = i;
        }
        i = 0;
        while (i < nodeCount - 1) {
            if (nodeX[i] > nodeX[i  +1]) {
                int swap = nodeX[i]; 
                nodeX[i] = nodeX[i + 1]; 
                nodeX[i + 1] = swap; 
                if (i) i--; 
            } else {
              i++; 
            }
        }

        //  Fill the pixels between node pairs.
        for (i = 0; i < nodeCount; i += 2) {
            if (nodeX[i] >= getWidth()) {
                break;
            }

            if (nodeX[i + 1] > 0) {
                if (nodeX[i] < 0) {
                    nodeX[i] = 0;
                }

                if (nodeX[i + 1] > getWidth()) {
                    nodeX[i + 1] = getWidth();
                }

                drawHorizontalLine(nodeX[i], pixelY, nodeX[i+1] - nodeX[i], color);
            }
        }
    }
}
