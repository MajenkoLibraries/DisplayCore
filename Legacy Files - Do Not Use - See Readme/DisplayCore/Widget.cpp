#include <DisplayCore.h>
#include <stdarg.h>

void Widget::setValue(int v) {
    _value = v;
    _redraw = true;
}

int Widget::getValue() {
    return _value;
}

void Widget::handleTouch() {
    if (!_touch) {
        return;
    }

    if (!isEnabled()) {
        return;
    }

    boolean pressed = _ts->isPressed();

    if (pressed != _dbPressed) {
        _dbPressed = pressed;
        if (!_dbPressed) {
            _dbStart = 0;
        } else {
            _dbStart = millis();
        }
    }

    if (_dbStart == 0) {
        pressed = false;
    } else {
        if (millis() - _dbStart > 50) {
            pressed = true;
        } else {
            pressed = false;
        }
    }
        

    if (pressed) {
        _tx = _ts->x();
        _ty = _ts->y();
    }

    boolean inBounds = (
        (_tx >= (_x + _sense_x)) && (_tx < (_x + _sense_x + _sense_w)) &&
        (_ty >= (_y + _sense_y)) && (_ty < (_y + _sense_y + _sense_h))
    );

    // Press

    if ((pressed && inBounds) && (!_active)) {
        _active = true;
        _st = millis();
        _sx = _tx - _x;
        _sy = _ty - _y;
        _rt = millis();
        _rp = 0;
        _redraw = true;
      //  draw(_dev, _x, _y);

        if (_press != NULL) {
            Event e = {this, _sx, _sy, _sx, _sy, EVENT_PRESS};
            _rx = _sx;
            _ry = _sy;
            _press(&e);
        }
    }

    // Release
    if ((!pressed) && (_active)) {
        _active = false;
        _et = millis();
        _ex = _tx - _x;
        _ey = _ty - _y;
        _redraw = true;
     //   draw(_dev, _x, _y);

        if (_release != NULL) {
            _rx = _ex;
            _ry = _ey;
            Event e = {this, _ex, _ey, _ex - _sx, _ex - _sy, EVENT_RELEASE};
            _release(&e);
        }

        if (((_et - _st) > 10) && ((_et - _st) < 2000)) {
            if (_tap != NULL) {
                _rx = _ex;
                _ry = _ey;
                Event e = {this, _ex, _ey, _ex - _sx, _ex - _sy, EVENT_TAP};
                _tap(&e);
            }
        }
    }

    if ((pressed && !inBounds) && _active) {
//        _active = false;
//        _redraw = true;
        Event e = {this, _ex, _ey, _ex - _sx, _ex - _sy, EVENT_RELEASE};
        _release(&e);
        //draw(_dev, _x, _y);
    }
    // Drag
    if ((pressed && inBounds) && _active) {
        _ex = _tx - _x;
        _ey = _ty - _y;
        if (_sx != _ex || _sy != _ey) {
            if (_drag != NULL) {
                _rx = _ex;
                _ry = _ey;
                Event e = {this, _ex, _ey, _ex - _sx, _ex - _sy, EVENT_DRAG};
                _drag(&e);
            }
        }
        // Key repeat

        if (_rp == 0) {
            _rt = millis();
            _rp = 1;
            if (_repeat != NULL) {
                _rx = _ex;
                _ry = _ey;
                Event e = {this, _ex, _ey, _ex - _sx, _ex - _sy, EVENT_REPEAT};
                _repeat(&e);
            }
        } else if (_rp == 1) {
            if (millis() - _rt >= 1000) {
                _rt = millis();
                _rp = 2;
                _rc = 0;
                if (_repeat != NULL) {
                    _rx = _ex;
                    _ry = _ey;
                    Event e = {this, _ex, _ey, _ex - _sx, _ex - _sy, EVENT_REPEAT};
                    _repeat(&e);
                }
            }

        } else if (_rp == 2) {
            if (millis() - _rt >= 200) {
                _rt = millis();
                if (_repeat != NULL) {
                    _rx = _ex;
                    _ry = _ey;
                    Event e = {this, _ex, _ey, _ex - _sx, _ex - _sy, EVENT_REPEAT};
                    _repeat(&e);
                }
                _rc++;
                if (_rc == 10) {
                    _rp = 3;
                }
            }
        } else if (_rp == 3) {
            if (millis() - _rt >= 50) {
                _rt = millis();
                if (_repeat != NULL) {
                    _rx = _ex;
                    _ry = _ey;
                    Event e = {this, _ex, _ey, _ex - _sx, _ex - _sy, EVENT_REPEAT};
                    _repeat(&e);
                }
            }
        }

        _sx = _ex;
        _sy = _ey;
    }
}

void Widget::draw(DisplayCore *dev, int x, int y, color_t t) { draw(dev, x, y); }
void Widget::drawTransformed(DisplayCore *dev, int x, int y, int transform) { draw(dev, x, y); }
void Widget::drawTransformed(DisplayCore *dev, int x, int y, int transform, color_t t) { draw(dev, x, y); }
void Widget::draw(DisplayCore &dev, int x, int y) { draw(&dev, x, y); }
void Widget::draw(DisplayCore &dev, int x, int y, color_t t) { draw(&dev, x, y, t); }
void Widget::drawTransformed(DisplayCore &dev, int x, int y, int transform) { drawTransformed(&dev, x, y, transform); }
void Widget::drawTransformed(DisplayCore &dev, int x, int y, int transform, color_t t) { drawTransformed(&dev, x, y, t); }

void Widget::render() {
    handleTouch();
    if (_redraw) {
        draw(_dev, _x, _y);
        _redraw = false;
    }
}

void Widget::redraw() {
    _redraw = true;
}

void Widget::setEnabled(boolean e) {
    if (e != _enabled) {
        _redraw = true;
    }
    _enabled = e;
}

boolean Widget::isEnabled() {
    return _enabled;
}

boolean Widget::isActive() {
    return _active;
}
