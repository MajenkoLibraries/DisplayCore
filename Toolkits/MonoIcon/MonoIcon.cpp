#include <MonoIcon.h>

void MonoIcon::draw(DisplayCore *dev, int16_t x, int16_t y) {

    int voff = 0;

    int fg_w = _icon[0];
    int fg_h = _icon[1];

    int fg_x = _sense_w/2 - fg_w/2;
    int fg_y = (_sense_h/2 - fg_h/2) - voff;;


    uint16_t buffer[_sense_w * _sense_h];
    Framebuffer565 fb(_sense_w, _sense_h, buffer);

    int th = 0;
    int tw = 0;

    if (_text != NULL) {
        fb.setFont(_font);
        fb.setTextColor(_textcol, _textcol);
        fb.setTextWrap(false);

        tw = fb.stringWidth(_text);
        th = fb.stringHeight(_text);
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
                fb.setPixel(px, py, _bg[py * _sense_w + px]);
            } else {
                int alpha = _icon[(py - fg_y) * fg_w + (px - fg_x)];
                uint16_t bg = _bg[py * _sense_w + px];
                uint16_t col = mix(bg, _color, alpha * 2);
                fb.setPixel(px, py, col);
            }
        }
    }

    if (_text != NULL) {
        fb.setCursor(_sense_w/2 - tw/2, _sense_h - th - 3);
        fb.print(_text);
    }

    fb.draw(dev, x, y);

//    dev->openWindow(x, y, _sense_w, _sense_h);
//    dev->windowData(buffer, _sense_w * _sense_h);
//    dev->closeWindow();
}
