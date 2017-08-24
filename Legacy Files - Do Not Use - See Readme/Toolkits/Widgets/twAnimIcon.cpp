#include <Widgets.h>

void twAnimIcon::draw(DisplayCore *dev, int x, int y) {

    int v = getValue();
    if (v >= _data->frames) {
        v = _data->frames;
    }

    dev->openWindow(x, y, _data->width, _data->height);
    dev->windowData((color_t*)_data->data + (v * (_data->width * _data->height)), _data->width * _data->height);
    dev->closeWindow();

	dev->setFont(_font);

    if (isEnabled()) {
        dev->setTextColor(_textColor, _bgColor);
    } else {
        dev->setTextColor(mix(_bgColor, _textColor, 50), _bgColor);
    }

	int _tw = dev->stringWidth(_txt);

	dev->setCursor(x + _data->width/2 - _tw/2, y + _data->height + 5);
	dev->print(_txt);
}

void twAnimIcon::setLabel(const char *t) {
    _txt = t;
    _redraw = true;
}
