#include <Widgets.h>

void twButton::draw(DisplayCore *dev, int x, int y) {
	dev->setFont(_font);

    color_t bg = getValue() ? _bgHi : _bgLo;
    color_t fg = getValue() ? _fgHi : _fgLo;

	int _tw = dev->stringWidth(_txt);
	int _th = dev->stringHeight(_txt);

    int _bgTop = _y + _bevel;
    int _bgBottom = _y + _height - _bevel;
    int _bgLeft = _x + _bevel;
    int _bgRight = _x + _width - _bevel;

    int _bgWidth = _width - (_bevel * 2);

    int _txtTop = _y + ((_height / 2) - (_th / 2));
    int _txtLeft = _x + ((_width / 2) - (_tw / 2));
    int _txtBottom = (_txtTop + _th);
    int _txtRight = (_txtLeft + _tw);

	for (int i = 0; i < _bevel; i++) {
		dev->drawLine(_x,      _y+i,    _x+_width-i-1, _y+i,    getValue() ? _blow : _bhi); 
		dev->drawLine(_x+i,    _y+_height-i-1, _x+_width-1,   _y+_height-i-1, getValue() ? _bhi : _blow); 
		dev->drawLine(_x+i,    _y,      _x+i,    _y+_height-i-1, getValue() ? _blow : _bhi); 
		dev->drawLine(_x+_width-i-1, _y+i,    _x+_width-i-1, _y+_height-1,  getValue() ? _bhi : _blow);
	}
  	dev->fillRectangle(_bgLeft, _bgTop, _bgWidth, _txtTop - _y, bg);
    dev->fillRectangle(_bgLeft, _txtBottom, _bgWidth, _bgBottom - _txtBottom, bg);
    dev->fillRectangle(_bgLeft, _txtTop, _txtLeft - _bgLeft, _th, bg);
    dev->fillRectangle(_txtRight, _txtTop, _bgRight - _txtRight, _th, bg);

	dev->setTextColor(fg, bg);
	dev->setCursor(_x + _width/2 - _tw/2, _y + _height/2 - _th/2);
	dev->print(_txt);
}

void twButton::setLabel(char *t) {
    _txt = t;
    _redraw = true;
}
