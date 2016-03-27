#include <NativeFB.h>

int vt = -1;

void cleanupTty() {
    if (vt > 0) {
        int cvt = 1;
        int d;
        ioctl(vt, KDGKBMODE, &d);
        ioctl(vt, KDSETMODE, KD_TEXT);
        ioctl(vt, VT_UNLOCKSWITCH, 1); 
        ioctl(vt, VT_ACTIVATE, cvt);
        ioctl(vt, VT_WAITACTIVE, cvt);
    }
}

void NativeFB::initializeDevice() {
    // First attempt to switch to a new TTY.
    char temp[100];
    struct vt_stat vtst;
    int cvt = -1;
    int tfd = -1;
    tfd = open("/dev/console", O_WRONLY, 0);
    if (tfd >= 0) {
        ioctl(tfd, VT_OPENQRY, &cvt);
        close(tfd);

        if (cvt >= 0) {
            sprintf(temp, "/dev/tty%d", cvt);
            vt = open(temp, O_RDWR);
            if (vt > 0) {
                int d;
                ioctl(vt, KDGKBMODE, &d);
                ioctl(vt, VT_GETSTATE, &vtst);
                ioctl(vt, KDSETMODE, KD_TEXT);
                ioctl(vt, KDSKBMODE, K_MEDIUMRAW);
                ioctl(vt, VT_UNLOCKSWITCH, 1); 
                ioctl(vt, VT_ACTIVATE, cvt);
                ioctl(vt, VT_WAITACTIVE, cvt);
                ioctl(vt, VT_LOCKSWITCH, 1); 
                ioctl(vt, KDSETMODE, KD_GRAPHICS);
                atexit(&cleanupTty);
            }
        }
    }

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

void NativeFB::setPixel(int x, int y, color_t c) {
    if (x < 0 || y < 0 || x >= _width || y >= _height) {
        return;
    }
    color_t *b16 = (color_t *)_buffer;
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

color_t NativeFB::colorAt(int x, int y) {
    if (x < 0 || y < 0 || x >= _width || y >= _height) {
        return 0;
    }
    color_t *b16 = (color_t *)_buffer;
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
    const char *msg = "0\n";
    int f = open("/sys/class/graphics/fb0/blank", O_RDWR);
    if (!f) {
        fprintf(stderr, "NativeFB Error: displayOn() requires privileged operation.\r\n");
        exit(10);
    }
    ::write(f, msg, 2);
    close(f);
}

void NativeFB::displayOff() {
    const char *msg = "1\n";
    int f = open("/sys/class/graphics/fb0/blank", O_RDWR);
    if (!f) {
        fprintf(stderr, "NativeFB Error: displayOff() requires privileged operation.\r\n");
        exit(10);
    }
    ::write(f, msg, 2);
    close(f);
}

void NativeFB::disableCursor() {
    const char *msg = "0\n";
    int f = open("/sys/class/graphics/fbcon/cursor_blink", O_RDWR);
    if (!f) {
        fprintf(stderr, "NativeFB Error: disableCursor() requires privileged operation.\r\n");
        exit(10);
    }
    ::write(f, msg, 2);
    close(f);
}

void NativeFB::enableCursor() {
    const char *msg = "1\n";
    int f = open("/sys/class/graphics/fbcon/cursor_blink", O_RDWR);
    if (!f) {
        fprintf(stderr, "NativeFB Error: enableCursor() requires privileged operation.\r\n");
        exit(10);
    }
    ::write(f, msg, 2);
    close(f);
}

int NativeFB::getWidth() {
    return _width;
}

int NativeFB::getHeight() {
    return _height;
}
