#include <LinuxEvent.h>

void LinuxEvent::initializeDevice() {
    char temp[100];
    int i = 0;
    while (1) {
        sprintf(temp, "/sys/class/input/input%d/name", i);
        int idfd = ::open(temp, O_RDONLY);
        if (idfd < 0) {
            fprintf(stderr, "LinuxEvent Error: Unable to find device '%s'.\r\n", _name);
            exit(10);
        }
        memset(temp, 0, 100);
        if (!::read(idfd, temp, 100)) {
            fprintf(stderr, "LinuxEvent Error: Unable to read from '%s'.\r\n", temp);
            ::close(idfd);
            exit(10);
        }
        ::close(idfd);
        while (temp[strlen(temp)-1] < ' ') {
            temp[strlen(temp)-1] = 0;
        }

        if (strcmp(temp, _name) == 0) {
            _devid = i;
            break;
        }
        i++;
    }

    sprintf(temp, "/dev/input/event%d", _devid);
    
    _fd = open(temp, O_RDONLY);
    if (_fd < 0) {
        fprintf(stderr, "LinuxEvent Error: Unable to open %s for reading.\r\n", temp);
        exit(10);
    }

    _pos.x = 0;
    _pos.y = 0;
    _pressed = false;
    _scale_x = 4096 / (_width);
    _scale_y = 4096 / (_height);
    _rotation = 0;
}

uint16_t LinuxEvent::x() {
    int x = _pos.x + _offset_x;
    int y = _pos.y + _offset_y;

    switch (_rotation) {
        case 0:
            return x;
        case 3:
            return _height - y;
        case 2:
            return _width - x;
        case 1:
            return y;
    }
    return 0;
}

uint16_t LinuxEvent::y() {
    int x = _pos.x + _offset_x;
    int y = _pos.y + _offset_y;

    switch (_rotation) {
        case 0:
            return y;
        case 3:
            return x;
        case 2:
            return _height - y;
        case 1:
            return _width - x;
    }
    return 0;
}

boolean LinuxEvent::isPressed() {
    return _pressed;
}

void LinuxEvent::sample() {
    struct event edata;

    struct timeval tv;
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(_fd, &rfds);
    tv.tv_sec = 0;
    tv.tv_usec = 10;

    int rv = select(_fd+1, &rfds, NULL, NULL, &tv);
    while (rv) {
        ::read(_fd, &edata, sizeof(struct event));

        if (edata.type == 3) { // touch event
            if (edata.code == 0) { // X
                _pos.x = edata.value * _width / 4095;
            } else if (edata.code == 1) { // Y
                _pos.y = edata.value * _height / 4095;
            }
            _pressed = true;
        } else if (edata.type == 1) {
            if (edata.code == 330) { // release event
                _pressed = false;
            }
        }

        FD_ZERO(&rfds);
        FD_SET(_fd, &rfds);
        tv.tv_sec = 0;
        tv.tv_usec = 10;
        rv = select(_fd+1, &rfds, NULL, NULL, &tv);
    }
}

uint16_t LinuxEvent::pressure() {
    return 0;
}

void LinuxEvent::setRotation(uint8_t r) {
    _rotation = r % 4;
}
