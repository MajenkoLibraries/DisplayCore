#include <LinuxEvent.h>

void LinuxEvent::initializeDevice() {
    char temp[100];

    _maxfd = 0;

    for (int i = 0; i < _MAX_IN_DEV; i++) {
        _fd[i] = -1;
    }

    for (int i = 0; i < _MAX_IN_DEV; i++) {
        sprintf(temp, "/dev/input/event%d", i);
        _fd[i] = ::open(temp, O_RDONLY);
        if (_fd[i] > _maxfd) {
            _maxfd = _fd[i];
        }
    }
    
    _pos.x = 0;
    _pos.y = 0;
    _pressed = false;
    _scale_x = 4096 / (_width);
    _scale_y = 4096 / (_height);
    _rotation = 0;
}

int LinuxEvent::x() {
    int x = (_pos.x * _width / 4095) + _offset_x;
    int y = (_pos.y * _height / 4095) + _offset_y;

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

int LinuxEvent::y() {
    int x = (_pos.x * _width / 4095) + _offset_x;
    int y = (_pos.y * _height / 4095) + _offset_y;

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
    for (int i = 0; i < _MAX_IN_DEV; i++) {
        if (_fd[i] >= 0) {
            FD_SET(_fd[i], &rfds);
        }
    }
    tv.tv_sec = 0;
    tv.tv_usec = 1000;

    int rv = select(_maxfd+1, &rfds, NULL, NULL, &tv);
    if (!rv) {
        return;
    }

    for (int i = 0; i < _MAX_IN_DEV; i++) {
        if (_fd[i] >= 0) {
            if (FD_ISSET(_fd[i], &rfds)) {
                ::read(_fd[i], &edata, sizeof(struct event));
                while (edata.type != 0)  {
                    switch (edata.type) {
                        case 1: // Button change
                            if (edata.code == 330) { // Mouse / TS
                                _pressed = (edata.value == 1);
                            } else {
                                if (edata.value >= 1) {
                                    _rxBuffer.write(edata.code);
                                }
                            }
                            break;

                        case 3: // Move
                            if (edata.code == 0) { // X
                                _pos.x = edata.value;
                            } else if (edata.code == 1) { // Y
                                _pos.y = edata.value;
                            }
                            break;
                    }
                    ::read(_fd[i], &edata, sizeof(struct event));
                }
            }
        }
    }
}

int LinuxEvent::rawX() {
    return _pos.x;
}

int LinuxEvent::rawY() {
    return _pos.y;
}

int LinuxEvent::pressure() {
    return 0;
}

void LinuxEvent::setRotation(int r) {
    _rotation = r % 4;
}
