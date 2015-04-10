#include <NativeFB.h>

void NativeFB::initializeDevice() {
    _fd = open("/dev/fb0", O_RDWR);

    if (!_fd) {
        fprintf(stderr, "Error opening /dev/fb0\r\n");
        exit(10);
    }

    if (ioctl (_fd, FBIOGET_FSCREENINFO, &_finfo)) {
        fprintf(stderr, "Error reading fixed information.\r\n");
        exit(10);
    }

    if (ioctl (_fd, FBIOGET_VSCREENINFO, &_vinfo)) {
        fprintf(stderr, "Error reading variable information.\r\n");
        exit(10);
    }

    _buffer = (uint8_t *)mmap(0, _finfo.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, _fd, 0);
    _width = _vinfo.xres;
    _height = _vinfo.yres;
}

void NativeFB::setPixel(int16_t x, int16_t y, uint16_t c) {
    if (x < 0 || y < 0 || x >= _width || y >= _height) {
        return;
    }
    uint16_t *b16 = (uint16_t *)_buffer;
    Color565 *cl = (Color565 *)&c;
    uint8_t r = cl->r << 3;
    uint8_t g = cl->g << 2;
    uint8_t b = cl->b << 3;

    if (r & 0b00001000) {
        r |= 0b00000111;
    }

    if (g & 0b00000100) {
        g |= 0b00000011;
    }

    if (b & 0b00001000) {
        b |= 0b00000111;
    }

    uint32_t pos;

    switch (_vinfo.bits_per_pixel) {
        case 16:
            b16[x + y * _width] = c;
            break;
        case 24:
            pos = x + y * _width * 3;
            _buffer[pos] = r;
            _buffer[pos+1] = g;
            _buffer[pos+2] = b;
            break;
            
        case 32:
            pos = x + y * _width * 4;
            _buffer[pos] = r;
            _buffer[pos+1] = g;
            _buffer[pos+2] = b;
            break;
    }
}

uint16_t NativeFB::colorAt(int16_t x, int16_t y) {
    if (x < 0 || y < 0 || x >= _width || y >= _height) {
        return 0;
    }
    uint16_t *b16 = (uint16_t *)_buffer;
    uint8_t r;
    uint8_t g;
    uint8_t b;

    uint32_t pos;

    switch (_vinfo.bits_per_pixel) {
        case 16:
            return b16[x + y * _width];
            break;
        case 24:
            pos = x + y * _width * 3;
            r = _buffer[pos];
            g = _buffer[pos+1];
            b = _buffer[pos+2];
            break;
            
        case 32:
            pos = x + y * _width * 4;
            r = _buffer[pos];
            g = _buffer[pos+1];
            b = _buffer[pos+2];
            break;
    }
    return rgb(r, g, b);
}

void NativeFB::displayOn() {
    char *msg = "0\n";
    int f = open("/sys/class/graphics/fb0/blank", O_RDWR);
    if (!f) {
        fprintf(stderr, "NativeFB Error: displayOn() requires privileged operation.\r\n");
        exit(10);
    }
    ::write(f, msg, 2);
    close(f);
}

void NativeFB::displayOff() {
    char *msg = "1\n";
    int f = open("/sys/class/graphics/fb0/blank", O_RDWR);
    if (!f) {
        fprintf(stderr, "NativeFB Error: displayOff() requires privileged operation.\r\n");
        exit(10);
    }
    ::write(f, msg, 2);
    close(f);
}

void NativeFB::disableCursor() {
    char *msg = "0\n";
    int f = open("/sys/class/graphics/fbcon/cursor_blink", O_RDWR);
    if (!f) {
        fprintf(stderr, "NativeFB Error: disableCursor() requires privileged operation.\r\n");
        exit(10);
    }
    ::write(f, msg, 2);
    close(f);
}

void NativeFB::enableCursor() {
    char *msg = "1\n";
    int f = open("/sys/class/graphics/fbcon/cursor_blink", O_RDWR);
    if (!f) {
        fprintf(stderr, "NativeFB Error: enableCursor() requires privileged operation.\r\n");
        exit(10);
    }
    ::write(f, msg, 2);
    close(f);
}


