#include <AnalogTouch.h>

void AnalogTouch::initializeDevice() {
    pinMode(_xl, INPUT);
    pinMode(_xr, INPUT);
    pinMode(_yu, INPUT);
    pinMode(_yd, INPUT);
    _pos.x = 0;
    _pos.y = 0;
    _pressed = false;
    _scale_x = 1900 / (_width);
    _scale_y = 1700 / (_height);
    _rotation = 0;
}

uint16_t AnalogTouch::x() {
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

uint16_t AnalogTouch::y() {
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

boolean AnalogTouch::isPressed() {
    return _pressed;
}

int AnalogTouch::getSample(uint8_t pin) {
    int samples[ANALOGTOUCH_SMPSIZE];
    for (int i = 0; i < ANALOGTOUCH_SMPSIZE; i++) {
        samples[i] = analogRead(pin);
    }
    int most = samples[0];
    int mostcount = 1;
    for(int pos = 0; pos < ANALOGTOUCH_SMPSIZE; pos++) {
        int current = samples[pos];
        int currentcount = 0;
        for(int inner = pos + 1; inner < ANALOGTOUCH_SMPSIZE; inner++) {
            if(samples[inner] == current) {
                currentcount++;
            }
        }
        if(currentcount > mostcount) {
            most = current;
            mostcount = currentcount;
        }
        // If we have less array slices left than the current
        // maximum count, then there is no room left to find
        // a bigger count.  We have finished early and we can
        // go home.
        if(ANALOGTOUCH_SMPSIZE - pos < mostcount) {
            break;
        }
    }
    if (mostcount < (ANALOGTOUCH_SMPSIZE/10)) {
        return 2000;
    }
    return most;
}

void AnalogTouch::sample() {
    pinMode(_xl, OUTPUT);
    pinMode(_xr, OUTPUT);
    pinMode(_yu, INPUT);
    pinMode(_yd, INPUT);
    digitalWrite(_xl, LOW);
    digitalWrite(_xr, HIGH);
    int x1 = getSample(_yu);

    pinMode(_xl, OUTPUT);
    pinMode(_xr, OUTPUT);
    pinMode(_yu, INPUT);
    pinMode(_yd, INPUT);
    digitalWrite(_xl, HIGH);
    digitalWrite(_xr, LOW);
    int x2 = getSample(_yu);

    pinMode(_xl, INPUT);
    pinMode(_xr, INPUT);
    pinMode(_yu, OUTPUT);
    pinMode(_yd, OUTPUT);
    digitalWrite(_yu, LOW);
    digitalWrite(_yd, HIGH);
    int y1 = getSample(_xl);

    pinMode(_xl, INPUT);
    pinMode(_xr, INPUT);
    pinMode(_yu, OUTPUT);
    pinMode(_yd, OUTPUT);
    digitalWrite(_yu, HIGH);
    digitalWrite(_yd, LOW);
    int y2 = getSample(_xl);

    _pressed = false;
    if (
        (x1 >= 10) &&
        (y1 >= 10) &&
        (x2 >= 10) &&
        (y2 >= 10) &&
        (x1 < 1000) &&
        (x2 < 1000) &&
        (y1 < 1000) &&
        (y2 < 1000) 
    ) {
        if (abs(x1 - x2) < 1000 && abs(y1 - y2) < 1000) {
            _pressed = true;
            _pos.x = (_width / 2) + ((x1 - x2) / _scale_x);
            _pos.y = (_height / 2) + ((y1 - y2) / _scale_y);
        }
    }

    _pressure = max(abs(x1 - x2), abs(y1 - y2));
}

uint16_t AnalogTouch::pressure() {
    return _pressure;
}

void AnalogTouch::setRotation(uint8_t r) {
    _rotation = r % 4;
}
