#ifndef _LCARSINTERFACE_H
#define _LCARSINTERFACE_H

#include <DisplayCore.h>
#include <LCARS.h>
#include <Average.h>

namespace LCARS {

    const color_t DarkOrange = rgb(0xff9900);
    const color_t MidOrange = rgb(0xff9966);
    const color_t LightOrange = rgb(0xffcc99);

    const color_t DarkRed = rgb(0xcc6666);
    const color_t MidRed = rgb(0xcc6699);
    const color_t LightRed = rgb(0xcc99cc);

    const color_t DarkBlue = rgb(0x9999cc);
    const color_t LightBlue = rgb(0x9999ff);

    const color_t Yellow = rgb(0xfffa35);
    const color_t White = rgb(0xffffff);

    class HBar : public Widget {
        private:
            color_t leftColor;
            color_t midColor;
            color_t rightColor;
            const char *leftText;
            const char *midText;
            const char *rightText;

        public:
            HBar(Touch &ts, DisplayCore &dev, int y, color_t lc, color_t mc, color_t rc, const char *lt, const char *mt, const char *rt) : 
                Widget(ts, dev, 0, y),
                leftColor(lc), midColor(mc), rightColor(rc), leftText(lt), midText(mt), rightText(rt) {}
                
            void setPixel(int x, int y, color_t c) {} // No drawing!

            void draw(DisplayCore *dev, int x, int y);

            void initializeDevice() { }
    };

    class HBarBend : public Widget {
        private:
            int bendType;
            color_t leftColor;
            color_t midColor;
            color_t rightColor;
            color_t endColor;
            int midPos;
            int midSize;
            int bendSize;
            const char *text;
            uint32_t _lastRender;

            boolean movedMid;
            boolean redraw;

        public:
            static const int BendDown = 0x01;
            static const int BendUp = 0x02;
            static const int BendLeft = 0x10;
            static const int BendRight = 0x20;

            HBarBend(
                Touch &ts, DisplayCore &dev, int x, int y,
                int bt, color_t lc, color_t mc, color_t rc, color_t ec, int mp, int ms, int bs, const char *t) : Widget(ts, dev, x, y),
                bendType(bt), leftColor(lc), midColor(mc), rightColor(rc), endColor(ec), midPos(mp), midSize(ms), bendSize(bs), text(t), movedMid(false) { setValue(mp); }
                
            void setPixel(int x, int y, color_t c) {} // No drawing!
            void setValue(int x);

            void draw(DisplayCore *dev, int x, int y);

            void initializeDevice() { }

            void render();
    };

    class Block : public Widget {
        private:
            int _width;
            int _height;
            color_t _color;
            const char *_text;

        public:
            Block(Touch &ts, DisplayCore &dev, int x, int y, int w, int h, color_t col, const char *txt) : Widget(ts, dev, x, y), 
                _width(w), _height(h), _color(col), _text(txt) {}
                
            void setPixel(int x, int y, color_t c) {} // No drawing!

            void draw(DisplayCore *dev, int x, int y);

            void initializeDevice() { }

    };

    class StaticText : public Widget {
        private:
            color_t _color;
            const uint8_t *_font;
            char _text[100];
            int _align;

        public:
            static const int AlignLeft = 0;
            static const int AlignRight = 1;
            static const int AlignCenter = 2;
            StaticText(Touch &ts, DisplayCore &dev, int x, int y, color_t col, const uint8_t *f, const char *txt) : Widget(ts, dev, x, y), 
                _color(col), _font(f), _align(AlignLeft) {
                memset(_text, 0, 100);
                strncpy(_text, txt, 99);
            }
                
            void setPixel(int x, int y, color_t c) {} // No drawing!

            void draw(DisplayCore *dev, int x, int y);

            void initializeDevice() { }

            void setAlign(int align);
            void setText(const char *txt);
    };

    class MiniScope : public Widget {
        private:
            Average<int> *data;
            static color_t scratchpad[276*84];

        public:
            MiniScope(Touch &ts, DisplayCore &dev, int x, int y) : Widget(ts, dev, x, y) {
                data = new Average<int>(256);
            }

        void setValue(int v);
        int getValue();
        int getAverage();
        void setPixel(int x, int y, color_t c);
        void draw(DisplayCore *dev, int x, int y);

        void initializeDevice() { }
    };

    class RectButton : public Widget {
        private:
            int _w;
            int _h;
            color_t _col_off;
            color_t _col_on;
            color_t _col_hi;
            const uint8_t *_font;
            const char *_text;
        public:
            RectButton(Touch &ts, DisplayCore &dev, int x, int y, int w, int h, color_t off, color_t on, color_t hi,
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

            void draw(DisplayCore *dev, int x, int y);

    };

    class OvalButton : public Widget {
        private:
            color_t _col_off;
            color_t _col_on;
            color_t _col_hi;
            const char *_text;

        public:
            OvalButton(
                Touch &ts, DisplayCore &dev,
                int x, int y,
                color_t off, color_t on, color_t hi,
                const char *text
            ) : Widget(ts, dev, x, y), _col_off(off), _col_on(on),
                _col_hi(hi), _text(text) {
                    _sense_x = 0;
                    _sense_y = 0;
                    _sense_w = 100;
                    _sense_h = 30;
                    _touch = true;
            }

            void draw(DisplayCore *dev, int x, int y);
    };

    class ExpandedOvalButton : public Widget {
        private:
            int _w;
            color_t _col_off;
            color_t _col_on;
            color_t _col_hi;
            color_t _col_st;
            const char *_text;
            const char *_title;
            const char *_off_text;
            const char *_on_text;

        public:
            ExpandedOvalButton(
                Touch &ts, DisplayCore &dev,
                int x, int y, int w,
                color_t off, color_t on, color_t hi, color_t st,
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

            void draw(DisplayCore *dev, int x, int y);
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

            void draw(DisplayCore *dev, int x, int y);
            void render();
#if ARDUINO >= 100
            virtual size_t write(uint8_t v);
#else
            virtual void write(uint8_t v);
#endif
    };

    class VScale : public Widget {
        private:
            color_t _lowCol;
            color_t _hiCol;
            color_t _overCol;
            boolean _valueChanged;
            int _realValue;
            uint32_t _lastRender;

        public:
            VScale(Touch &ts, DisplayCore &dev, int x, int y, color_t lowCol, color_t hiCol, color_t overCol) : Widget(ts, dev, x, y), _lowCol(lowCol), _hiCol(hiCol), _overCol(overCol) { 
                _valueChanged = false; 
                _touch = true;
                _sense_x = 0;
                _sense_y = 0;
                _sense_w = 20;
                _sense_h = 202;
            }
            

            void setValue(int v);
            void draw(DisplayCore *dev, int x, int y);
            void render();
    };
};

#endif


