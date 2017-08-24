#include <twText.h>

void twText::draw(DisplayCore *dev, int x, int y) {
    dev->startBuffer();
    dev->setTextColor(_color, Color::Black);
    dev->setFont(_font);
    switch (_align) {
        default:
        case AlignLeft:
            dev->setCursor(x, y);
            break;
        case AlignRight:
            dev->setCursor(x - dev->stringWidth(_text), y);
            break;
        case AlignCenter:
            dev->setCursor(x - dev->stringWidth(_text) / 2, y);
            break;
    }
    dev->print(_text);
    dev->endBuffer();
}


void twText::setAlign(uint8_t align) {
    _align = align;
}

void twText::setText(const char *txt) {
    if (strcmp(txt, _text) != 0) {
        memset(_text, 0, 100);
        strncpy(_text, txt, 99);
        _redraw = true;
    }
}

