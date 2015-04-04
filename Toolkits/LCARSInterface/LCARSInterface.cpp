#include <LCARSInterface.h>

namespace LCARS {

    void drawOuterQuadrant(DisplayCore *dev, int16_t x0, int16_t y0, uint16_t r, uint8_t corner, uint16_t color) {
        int16_t f = 1 - r;
        int16_t ddF_x = 1;
        int16_t ddF_y = -2 * r;
        int16_t x = 0;
        int16_t y = r;

        while (x<y) {
            if (f >= 0) {
                y--;
                ddF_y += 2;
                f += ddF_y;
            }
            x++;
            ddF_x += 2;
            f += ddF_x;
            if (corner & 0x4) {
                dev->drawLine(x0 + x, y0 + y-1, x0, y0 + y-1, color);
                dev->drawLine(x0 + y, y0 + x-1, x0, y0 + x-1, color);
            }
            if (corner & 0x2) {
                dev->drawLine(x0 + x, y0 - y, x0, y0 - y, color);
                dev->drawLine(x0 + y, y0 - x, x0, y0 - x, color);
            }
            if (corner & 0x8) {
                dev->drawLine(x0 - x, y0 + y, x0, y0 + y, color);
                dev->drawLine(x0 - y, y0 + x, x0, y0 + x, color);
            }
            if (corner & 0x1) {
                dev->drawLine(x0 - x, y0 - y, x0, y0 - y, color);
                dev->drawLine(x0 - y, y0 - x, x0, y0 - x, color);
            }
        }
    }

    void drawInnerQuadrant(DisplayCore *dev, int16_t x0, int16_t y0, uint16_t r, uint8_t corner, uint16_t color) {
        int16_t f     = 1 - r;
        int16_t ddF_x = 1;
        int16_t ddF_y = -2 * r;
        int16_t x     = 0;
        int16_t y     = r;

        while (x<y) {
            if (f >= 0) {
                y--;
                ddF_y += 2;
                f     += ddF_y;
            }
            x++;
            ddF_x += 2;
            f     += ddF_x;
            if (corner & 0x4) {
                dev->drawLine(x0 + x, y0 + y, x0-r, y0 + y, color);
                dev->drawLine(x0 + y, y0 + x, x0-r, y0 + x, color);
            }
            if (corner & 0x2) {
                dev->drawLine(x0 + x, y0 - y, x0-r, y0 - y, color);
                dev->drawLine(x0 + y, y0 - x, x0-r, y0 - x, color);
            }
            if (corner & 0x8) {
                dev->drawLine(x0 - x, y0 + y, x0-r, y0 + y, color);
                dev->drawLine(x0 - y, y0 + x, x0-r, y0 + x, color);
            }
            if (corner & 0x1) {
                dev->drawLine(x0 - x, y0 - y, x0-r, y0 - y, color);
                dev->drawLine(x0 - y, y0 - x, x0-r, y0 - x, color);
            }
        }
    }

    void HBar::draw(DisplayCore *dev, int16_t x, int16_t y) {
        drawOuterQuadrant(dev, 10, y + 10, 10, 0x01, leftColor);
        drawOuterQuadrant(dev, 10, y + 9, 10, 0x08, leftColor);
        dev->fillRectangle(10, y + 0, 20, 20, leftColor);
        dev->fillRectangle(35, y + 0, 730, 20, midColor);
        drawOuterQuadrant(dev, 790, y + 10, 10, 0x02, rightColor);
        drawOuterQuadrant(dev, 790, y + 10, 10, 0x04, rightColor);
        dev->fillRectangle(770, y + 0, 20, 20, rightColor);
        dev->setTextColor(Yellow, Color::Black);
        dev->setFont(Fonts::LCARS24);
        if (leftText != NULL) {
            dev->setCursor(35, y - 3);
            dev->print(leftText);
        }
        if (midText != NULL) {
            dev->setCursor(400 - dev->stringWidth(midText)/2, y - 3);
            dev->print(midText);
        }
        if (rightText != NULL) {
            dev->setCursor(765 - dev->stringWidth(rightText), y - 3);
            dev->print(rightText);
        }
    }

    void HBarBend::draw(DisplayCore *dev, int16_t x, int16_t y) {
        if ((bendType & BendUp) && (bendType & BendLeft)) {
            // Bend portion
            if (!movedMid || _redraw) {
                dev->fillRectangle(0, y, 80, bendSize, leftColor);                                  // Left bend extension
                dev->fillRectangle(50, y + 20, bendSize + 10, 50, leftColor);                       // Left bend fill
                drawOuterQuadrant(dev, 50, y + bendSize - 1, 50, 0x8, leftColor);                   // Left bend outside
                drawInnerQuadrant(dev, 100, y + bendSize + 19, 20, 0x8, leftColor);                 // Left bend inside
                dev->fillRectangle(775, y + bendSize + 40, 25, 10, endColor);                       // End bit
                dev->setFont(Fonts::LCARS16);
                dev->setTextColor(Color::Black, leftColor);
                dev->setCursor(75 - (dev->stringWidth(text)), y + 5);
                dev->print(text);
            }

            // Horizontal bar
            dev->fillRectangle(80, y + bendSize + 40, midPos + 20, 10, leftColor);                   // Left portion of horizontal
            dev->fillRectangle(80 + midPos + 20, y + bendSize + 40, 5, 10, Color::Black);            // Left gap
            dev->fillRectangle(85 + midPos + 20, y + bendSize + 40, midSize - 10, 10, midColor);     // Mid section
            dev->fillRectangle(75 + midPos + 20 + midSize, y + bendSize + 40, 5, 10, Color::Black);  // Right gap
            dev->fillRectangle(80 + midPos + 20 + midSize, y + bendSize + 40, 670 - midPos - midSize, 10, rightColor);    // RIght section
            movedMid = false;
            _redraw = false;
            return;
        }

        if ((bendType & BendDown) && (bendType & BendLeft)) {
            dev->fillRectangle(80, y, midPos + 20, 10, leftColor);
            dev->fillRectangle(80 + midPos + 20, y, 5, 10, Color::Black);
            dev->fillRectangle(85 + midPos + 20, y, midSize - 10, 10, midColor);
            dev->fillRectangle(75 + midPos + 20 + midSize, y, 5, 10, Color::Black);  // Right gap
            dev->fillRectangle(80 + midPos + 20 + midSize, y, 670 - midPos - midSize, 10, rightColor);

            // Bend portion
            if (!movedMid || _redraw) {
                dev->fillRectangle(50, y, 30, 50, leftColor); 
                drawInnerQuadrant(dev, 100, y + 30, 20, 0x1, leftColor);
                drawOuterQuadrant(dev, 50, y + 50, 50, 0x1, leftColor);
                dev->fillRectangle(0, y + 50, 80, bendSize, leftColor);
                dev->fillRectangle(775, y, 25, 10, endColor);
                dev->setFont(Fonts::LCARS16);
                dev->setTextColor(Color::Black, leftColor);
                dev->setCursor(75 - (dev->stringWidth(text)), y + 28 + bendSize);
                dev->print(text);
            }
            movedMid = false;
            _redraw = false;
            return;
        }
    }

    void HBarBend::setValue(uint16_t x) {
        if (x != _value) {
            movedMid = true;
            if (x > 670 - midSize) {
                x = 670 - midSize;
            }
            _value = x;
        }
    }


    void HBarBend::render() {
        if (midPos > _value) {
            int dif = (midPos - _value) / 4;
            if (dif <= 0) {
                dif = 1;
            }
            midPos -= dif;
            movedMid = true;
        } else if (midPos < _value) {
            int dif = (_value - midPos) / 4;
            if (dif <= 0) {
                dif = 1;
            }
            midPos += dif;
            movedMid = true;
        }
        if (_redraw || movedMid) {
            draw(_dev, _x, _y);
            _redraw = false;
        }
    }

    void Block::draw(DisplayCore *dev, int16_t x, int16_t y) {
        dev->fillRectangle(x, y, _width, _height, _color);
        dev->setTextColor(Color::Black, _color);
        dev->setFont(Fonts::LCARS16);
        dev->setCursor(x + _width - 5 - dev->stringWidth(_text), y + _height - 22);
        dev->print(_text);
    }

    void StaticText::draw(DisplayCore *dev, int16_t x, int16_t y) {
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
                dev->setCursor(x, y - dev->stringWidth(_text) / 2);
                break;
        }
        dev->print(_text);
    }

    void StaticText::setAlign(uint8_t align) {
        _align = align;
    }

    void StaticText::setText(const char *txt) {
        memset(_text, 0, 100);
        strncpy(_text, txt, 99);
        _redraw = true;
    }

    uint16_t MiniScope::scratchpad[276*84];

    void MiniScope::setValue(int v) {
        if (v < 0) v = 0;
        if (v > 4095) v = 4095;
        data->push(v);
        _redraw = true;
    }

    int MiniScope::getValue() {
        return data->get(1);
    }

    int MiniScope::getAverage() {
        return data->mean();
    }

    void MiniScope::setPixel(int16_t x, int16_t y, uint16_t c) {
        if (x < 0 || y < 0 || x > 275 || y > 83) {
            return;
        }
        scratchpad[x + y * 276] = c;
    }

    void MiniScope::draw(DisplayCore *dev, int16_t x, int16_t y) {
        for (int i = 0; i < 276*84; i++) {
            scratchpad[i] = 0;
        }
        for (int i = 0; i < 254; i++) {
            drawLine(i, 73 - (data->get(255-i) >> 6)-1, i+1, 73 - (data->get(254-i) >> 6)-1, DarkRed);            
            drawLine(i, 73 - (data->get(255-i) >> 6)+1, i+1, 73 - (data->get(254-i) >> 6)+1, DarkRed);            
            drawLine(i, 73 - (data->get(255-i) >> 6), i+1, 73 - (data->get(254-i) >> 6), LightRed);           
        }
        int ld = (uint16_t)data->get(1) >> 6;
        
        fillTriangle(260, 73-ld, 275, 73-ld-10, 275, 73-ld+10, DarkRed);
        
        drawLine(0, 10, 255, 10, DarkOrange);
        drawLine(0, 41, 255, 41, DarkOrange);
        drawLine(0, 73, 255, 73, DarkOrange);
        drawLine(0, 10, 0, 73, DarkOrange);
        drawLine(31, 10, 31, 73, DarkOrange);
        drawLine(63, 10, 63, 73, DarkOrange);
        drawLine(95, 10, 95, 73, DarkOrange);
        drawLine(127, 10, 127, 73, DarkOrange);
        drawLine(159, 10, 159, 73, DarkOrange);
        drawLine(191, 10, 191, 73, DarkOrange);
        drawLine(223, 10, 223, 73, DarkOrange);
        drawLine(255, 10, 255, 73, DarkOrange);
        dev->openWindow(x, y, 276, 84);
        dev->windowData(scratchpad, 276*84);
        dev->closeWindow();
    }

    void RectButton::draw(DisplayCore *dev, int16_t x, int16_t y) {
        if (_active) {
            dev->fillRectangle(x, y, _w, _h, _col_hi);
            dev->setTextColor(Color::Black, _col_hi);
        } else if (_value == 0) {
            dev->fillRectangle(x, y, _w, _h, _col_off);
            dev->setTextColor(Color::Black, _col_off);
        } else {
            dev->fillRectangle(x, y, _w, _h, _col_on);
            dev->setTextColor(Color::Black, _col_on);
        }
        dev->setFont(_font);
        dev->setCursor(
            _x + _w - 5 - dev->stringWidth(_text),
            _y + _h/2 - dev->stringHeight(_text)/2
        );
        dev->print(_text);
    }

    void OvalButton::draw(DisplayCore *dev, int16_t x, int16_t y) {
        uint16_t col = _col_on;
        if (_active) {
            col = _col_hi;
        } else if (_value == 0) {
            col = _col_off;
        }

        drawOuterQuadrant(dev, _x + 15, _y + 15, 15, 0x1, col);
        drawOuterQuadrant(dev, _x + 15, _y + 14, 15, 0x8, col);
        dev->fillRectangle(_x + 15, _y, 70, 30, col);
        drawOuterQuadrant(dev, _x + 85, _y + 15, 15, 0x2, col);
        drawOuterQuadrant(dev, _x + 85, _y + 15, 15, 0x4, col);
        dev->setFont(Fonts::LCARS24);
        dev->setTextColor(Color::Black, col);
        int w = _dev->stringWidth(_text);
        int h = _dev->stringHeight(_text);
        dev->setCursor(_x + 85 - w, _y + 15 - h / 2);
        dev->print(_text);
    }

    void ExpandedOvalButton::draw(DisplayCore *dev, int16_t x, int16_t y) {
        uint16_t col = _col_on;
        if (_active) {
            col = _col_hi;
        } else if (_value == 0) {
            col = _col_off;
        }

        drawOuterQuadrant(dev, _x + 25, _y + 25, 25, 0x1, col);
        drawOuterQuadrant(dev, _x + 25, _y + 24, 25, 0x8, col);
        dev->fillRectangle(_x + 25, _y, 60, 50, col);
        dev->fillRectangle(_x + 85, _y, _w, 50, Color::Black);
        drawOuterQuadrant(dev, _x + 85 + _w, _y + 25, 25, 0x2, col);
        drawOuterQuadrant(dev, _x + 85 + _w, _y + 25, 25, 0x4, col);
        dev->setFont(Fonts::LCARS30);
        dev->setTextColor(Color::Black, col);
        int w = _dev->stringWidth(_text);
        int h = _dev->stringHeight(_text);
        dev->setCursor(_x + 80 - w, _y + 25 - h / 2);
        dev->print(_text);
        _dev->setTextColor(col, Color::Black);
        _dev->setCursor(_x + 90, _y);
        _dev->print(_title);
        _dev->setFont(Fonts::LCARS20);
        _dev->setCursor(_x + 90, _y + 30);
        _dev->setTextColor(_col_st, Color::Black);
        _dev->print(getValue() == 0 ? _off_text : _on_text);
    }

    void MessageLog::setValue(int v) {
        setFont(Fonts::LCARS16);
        if (v == '\n') {
            strcpy(_data[0], _data[1]);
            strcpy(_data[1], _data[2]);
            strcpy(_data[2], _data[3]);
            strcpy(_data[3], _data[4]);
            _data[4][0] = 0;
            _cpos = 0;
            _redraw = true;
            _full = true;
            _mix_percent = 255;
            return;
        }

        if (stringWidth(_data[4]) >= 400) {
            strcpy(_data[0], _data[1]);
            strcpy(_data[1], _data[2]);
            strcpy(_data[2], _data[3]);
            strcpy(_data[3], _data[4]);
            _data[4][0] = 0;
            _cpos = 0;
            _redraw = true;
            _full = true;
            _mix_percent = 255;
        }
        _data[4][_cpos++] = v;
        _data[4][_cpos] = 0;
    }

    void MessageLog::setValue(const char *str) {
        for (int i = 0; i < strlen(str); i++) {
            setValue(str[i]);
        }
    }

    void MessageLog::render() {
        if (_mix_percent > 0) {
            _mix_percent--;
            _redraw = true;
        }
        if (_redraw) {
            draw(_dev, _x, _y);
            _redraw = false;
        }
    }

    void MessageLog::draw(DisplayCore *dev, int16_t x, int16_t y) {
        dev->setFont(Fonts::LCARS16);
        if (_full) {
            dev->fillRectangle(x, y, 420, 76, Color::Black);
            dev->setTextColor(LCARS::DarkRed, Color::Black);
            dev->setCursor(x, y);
            dev->setTextWrap(false);
            dev->print(_data[0]);
            dev->setCursor(x, y + 19);
            dev->print(_data[1]);
            dev->setCursor(x, y + 38);
            dev->print(_data[2]);
            _full = false;
        }
        uint16_t lcol = mix(LCARS::DarkRed, LCARS::White, _mix_percent);
        dev->setCursor(x, y + 57);
        dev->setTextColor(lcol, Color::Black);
        dev->print(_data[3]);
    }

    size_t MessageLog::write(uint8_t v) {
        setValue((int)v);
        return 1;
    }

};
