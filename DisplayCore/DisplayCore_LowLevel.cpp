#include <DisplayCore.h>
#include <stdarg.h>

void DisplayCore::translateCoordinates(int *x, int *y) {
    int t;
    switch (rotation) {
        case 1:
            t = *x;
            *x = getWidth() - *y;
            *y = t;
            break;
        case 2:
            *x = getWidth() - *x;
            *y = getHeight() - *y;
            break;
        case 3:
            t = *x;
            *x = *y;
            *y = getHeight() - t;
            break;
    }
}

#if defined(__PIC32MX__) || defined(__PIC32MZ__)
p32_ioport *DisplayCore::getPortInformation(uint8_t pin, uint32_t *mask) {
    uint32_t portno = digitalPinToPort(pin);
    if (portno == NOT_A_PIN) {
        return NULL;
    }
    if (mask != NULL) {
        *mask = digitalPinToBitMask(pin);
    }
    return (p32_ioport *)portRegisters(portno);
}
#endif

int DisplayCore::getWidth() {
    return _width;
}

int DisplayCore::getHeight() {
    return _height;
}

void DisplayCore::setPixel(int x, int y, int z, color_t c) {
    point3d p3d = {x, y, z};
    point2d p2d = map3Dto2D(p3d);
    setPixel(p2d.x, p2d.y, c);
}

