#include <MonoIcon.h>

void MonoIcon::setPixel(int x, int y, color_t col) {
    if (x < 0 || y < 0 || x >= _sense_w || y >= _sense_h) return;
    uint32_t offset = y * _sense_w + x;
    _buffer[offset] = col;
}

color_t MonoIcon::colorAt(int x, int y) {
    if (x < 0 || y < 0 || x >= _sense_w || y >= _sense_h) return 0;
    uint32_t offset = y * _sense_w + x;
    return _buffer[offset];
}

void MonoIcon::draw(DisplayCore *dev, int x, int y) {

    int voff = 0;

    color_t color = _color;
//    if (!_enabled) {
//        color = Color::Gray60;
//    }

    color_t buffer[_sense_w * _sense_h];

    _buffer = buffer;

    int th = 0;
    int tw = 0;

    if (_icon != NULL) {
        int fg_w = _icon[0];
        int fg_h = _icon[1];

        int fg_x = _sense_w/2 - fg_w/2;
        int fg_y = (_sense_h/2 - fg_h/2) - voff;;

        if (_text != NULL) {
            setFont(_font);
            setTextColor(_textcol, _textcol);
            setTextWrap(false);

            tw = stringWidth(_text);
            th = stringHeight(_text);
        }

        for (int py = 0; py < _sense_h; py++) {
            for (int px = 0; px < _sense_w; px++) {
                // If we are outside the bounds of the icon then just paint the background.
                if (
                    (px <= fg_x) ||
                    (px >= (fg_x + fg_w)) ||
                    (py <= fg_y) ||
                    (py >= (fg_y + fg_h))
                ) {
                    setPixel(px, py, _bg[py * _sense_w + px]);
                } else {
                    int alpha = _icon[(py - fg_y) * fg_w + (px - fg_x)];
                    color_t bg = _bg[py * _sense_w + px];
                    color_t col = mix(bg, color, alpha * 2);
                    setPixel(px, py, col);
                }
            }
        }

        if (_text != NULL) {
            setCursor(_sense_w/2 - tw/2, _sense_h - th - 3);
            print(_text);
        }
    } else {
        for (int py = 0; py < _sense_h; py++) {
            for (int px = 0; px < _sense_w; px++) {
                setPixel(px, py, _bg[py * _sense_w + px]);
            }
        }

        setFont(_font);
        setTextColor(_textcol, _textcol);
        setTextWrap(false);
        tw = stringWidth(_text);
        th = stringHeight(_text);

        setCursor(_sense_w/2 - tw/2, _sense_h/2 - th/2);
        print(_text);
    }

    dev->openWindow(x, y, _sense_w, _sense_h);
    dev->windowData(_buffer, _sense_w * _sense_h);
    dev->closeWindow();
}

void MonoIcon::setColor(color_t c) {
    _color = c;
    redraw();
}

void MonoIcon::setIcon(const uint8_t *i) {
    _icon = i;
    redraw();
}
