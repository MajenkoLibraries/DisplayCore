#ifndef _LCARSINTERFACE_H
#define _LCARSINTERFACE_H

#include <DisplayCore.h>
#include <LCARS.h>
#include <Average.h>

namespace LCARS {

    const uint16_t DarkOrange = rgb(0xff9900);
    const uint16_t MidOrange = rgb(0xff9966);
    const uint16_t LightOrange = rgb(0xffcc99);

    const uint16_t DarkRed = rgb(0xcc6666);
    const uint16_t MidRed = rgb(0xcc6699);
    const uint16_t LightRed = rgb(0xcc99cc);

    const uint16_t DarkBlue = rgb(0x9999cc);
    const uint16_t LightBlue = rgb(0x9999ff);

    const uint16_t Yellow = rgb(0xfffa35);
    const uint16_t White = rgb(0xffffff);

    class HBar : public Widget {
        private:
            uint16_t leftColor;
            uint16_t midColor;
            uint16_t rightColor;
            const char *leftText;
            const char *midText;
            const char *rightText;

        public:
            HBar(Touch &ts, DisplayCore &dev, int y, uint16_t lc, uint16_t mc, uint16_t rc, const char *lt, const char *mt, const char *rt) : 
                Widget(ts, dev, 0, y),
                leftColor(lc), midColor(mc), rightColor(rc), leftText(lt), midText(mt), rightText(rt) {}
                
            void setPixel(int16_t x, int16_t y, uint16_t c) {} // No drawing!

            void draw(DisplayCore *dev, int16_t x, int16_t y);

            void initializeDevice() { }
    };

    class HBarBend : public Widget {
        private:
            uint8_t bendType;
            uint16_t leftColor;
            uint16_t midColor;
            uint16_t rightColor;
            uint16_t endColor;
            uint16_t midPos;
            uint16_t midSize;
            uint16_t bendSize;
            const char *text;

            boolean movedMid;
            boolean redraw;

        public:
            static const uint8_t BendDown = 0x01;
            static const uint8_t BendUp = 0x02;
            static const uint8_t BendLeft = 0x10;
            static const uint8_t BendRight = 0x20;

            HBarBend(
                Touch &ts, DisplayCore &dev, int x, int y,
                uint8_t bt, uint16_t lc, uint16_t mc, uint16_t rc, uint16_t ec, uint16_t mp, uint16_t ms, uint16_t bs, const char *t) : Widget(ts, dev, x, y),
                bendType(bt), leftColor(lc), midColor(mc), rightColor(rc), endColor(ec), midPos(mp), midSize(ms), bendSize(bs), text(t), movedMid(false) { setValue(mp); }
                
            void setPixel(int16_t x, int16_t y, uint16_t c) {} // No drawing!
            void setValue(uint16_t x);

            void draw(DisplayCore *dev, int16_t x, int16_t y);

            void initializeDevice() { }

            void render();
    };

    class Block : public Widget {
        private:
            int _width;
            int _height;
            uint16_t _color;
            const char *_text;

        public:
            Block(Touch &ts, DisplayCore &dev, int x, int y, int w, int h, uint16_t col, const char *txt) : Widget(ts, dev, x, y), 
                _width(w), _height(h), _color(col), _text(txt) {}
                
            void setPixel(int16_t x, int16_t y, uint16_t c) {} // No drawing!

            void draw(DisplayCore *dev, int16_t x, int16_t y);

            void initializeDevice() { }

    };

    class StaticText : public Widget {
        private:
            uint16_t _color;
            const uint8_t *_font;
            char _text[100];
            uint8_t _align;

        public:
            static const uint8_t AlignLeft = 0;
            static const uint8_t AlignRight = 1;
            static const uint8_t AlignCenter = 2;
            StaticText(Touch &ts, DisplayCore &dev, int x, int y, uint16_t col, const uint8_t *f, const char *txt) : Widget(ts, dev, x, y), 
                _color(col), _font(f), _align(AlignLeft) {
                memset(_text, 0, 100);
                strncpy(_text, txt, 99);
            }
                
            void setPixel(int16_t x, int16_t y, uint16_t c) {} // No drawing!

            void draw(DisplayCore *dev, int16_t x, int16_t y);

            void initializeDevice() { }

            void setAlign(uint8_t align);
            void setText(const char *txt);
    };

    class MiniScope : public Widget {
        private:
            Average<int> *data;
            static uint16_t scratchpad[276*84];

        public:
            MiniScope(Touch &ts, DisplayCore &dev, int x, int y) : Widget(ts, dev, x, y) {
                data = new Average<int>(256);
            }

        void setValue(int v);
        int getValue();
        int getAverage();
        void setPixel(int16_t x, int16_t y, uint16_t c);
        void draw(DisplayCore *dev, int16_t x, int16_t y);

        void initializeDevice() { }
    };

    class RectButton : public Widget {
        private:
            int _w;
            int _h;
            uint16_t _col_off;
            uint16_t _col_on;
            uint16_t _col_hi;
            const uint8_t *_font;
            const char *_text;
        public:
            RectButton(Touch &ts, DisplayCore &dev, int x, int y, int w, int h, uint16_t off, uint16_t on, uint16_t hi,
                        const uint8_t *f, const char *t) :
                Widget(ts, dev, x, y),
                _w(w), _h(h), _col_off(off), _col_on(on), _col_hi(hi),
                _font(f), _text(t)
            {
                _sense_x = 0;
                _sense_y = 0;
                _sense_w = w;
                _sense_h = h;
                _touch = true;
            }

            void draw(DisplayCore *dev, int16_t x, int16_t y);

    };

    class OvalButton : public Widget {
        private:
            uint16_t _col_off;
            uint16_t _col_on;
            uint16_t _col_hi;
            const char *_text;

        public:
            OvalButton(
                Touch &ts, DisplayCore &dev,
                int x, int y,
                uint16_t off, uint16_t on, uint16_t hi,
                const char *text
            ) : Widget(ts, dev, x, y), _col_off(off), _col_on(on),
                _col_hi(hi), _text(text) {
                    _sense_x = 0;
                    _sense_y = 0;
                    _sense_w = 100;
                    _sense_h = 30;
                    _touch = true;
            }

            void draw(DisplayCore *dev, int16_t x, int16_t y);
    };

    class ExpandedOvalButton : public Widget {
        private:
            int _w;
            uint16_t _col_off;
            uint16_t _col_on;
            uint16_t _col_hi;
            uint16_t _col_st;
            const char *_text;
            const char *_title;
            const char *_off_text;
            const char *_on_text;

        public:
            ExpandedOvalButton(
                Touch &ts, DisplayCore &dev,
                int x, int y, int w,
                uint16_t off, uint16_t on, uint16_t hi, uint16_t st,
                const char *text,
                const char *title,
                const char *offtext,
                const char *ontext
            ) : Widget(ts, dev, x, y), _w(w), _col_off(off), _col_on(on),
                _col_hi(hi), _col_st(st), _text(text), _title(title), 
                _off_text(offtext), _on_text(ontext) {
                    _sense_x = 0;
                    _sense_y = 0;
                    _sense_w = 110 + _w;
                    _sense_h = 50;
                    _touch = true;
            }

            void draw(DisplayCore *dev, int16_t x, int16_t y);
    };

    class MessageLog : public Widget {
        private:
            char _data[5][300];
            int _cpos;
            int _mix_percent;
            boolean _full;
        public:
            MessageLog(Touch &ts, DisplayCore &dev, int x, int y) : Widget(ts, dev, x, y), _full(true) {}

            void setValue(int v);
            void setValue(const char *str);

            void draw(DisplayCore *dev, int16_t x, int16_t y);
            void render();
            size_t write(uint8_t v);
    };
};

#endif


