#include <Widgets.h>

void twIcon::draw(DisplayCore *dev, int x, int y) {

    if (isEnabled()) {
        dev->openWindow(x, y, _width, _height);
        dev->windowData((color_t*)_icon, _width * _height);
        dev->closeWindow();
    } else {
        dev->openWindow(x, y, _width, _height);
        int p = 0;
        for (int iy = 0; iy < _height; iy++) {
            for (int ix = 0; ix < _width; ix++) {
                color_t c = _icon[p];
                uint8_t r = c >> 11;
                uint8_t g = c >> 5 & 0b111111;
                uint8_t b = c & 0b11111;

                r <<= 3;
                g <<= 2;
                b <<= 3;
                c = mix(_bgColor, (r + g + b) / 3, 50);
                c = rgb(c, c, c);
                dev->windowData(c);
                p++;
            }
        }
        dev->closeWindow();
    }

	dev->setFont(_font);

    if (isEnabled()) {
        dev->setTextColor(_textColor, _bgColor);
    } else {
        dev->setTextColor(mix(_bgColor, _textColor, 50), _bgColor);
    }

	int _tw = dev->stringWidth(_txt);

	dev->setCursor(x + _width/2 - _tw/2, y + _height + 5);
	dev->print(_txt);
}

void twIcon::setLabel(const char *t) {
    _txt = t;
    _redraw = true;
}
