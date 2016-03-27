#ifndef _GCI_WIDGET_H
#define _GCI_WIDGET_H

#include <WProgram.h>

#include <DisplayCore.h>
#include <SD.h>

#define IMG_BUFSZ 256

struct gcihdr {
	uint16_t width;
	uint16_t height;
	uint8_t mode;
	uint8_t fdel;
	uint16_t frames;
} __attribute__((packed));

class gciWidget : public Widget {
    private:
        void load();
	public:
        bool _loaded;
        File *_file;
        gcihdr _header;
        const char *_filename;
        const char *_widgetname;
		uint32_t _offset;

		gciWidget(Touch &ts, DisplayCore &dev, const char *fn, const char *wn)
            : Widget(ts, dev, 0, 0), _filename(fn), _widgetname(wn), _loaded(false) {
            _touch = true;
        }

        void draw(DisplayCore *dev, int x, int y);
		int getFrames();

        int getWidth() { return _sense_w; }
        int getHeight() { return _sense_h; }
        void setValue(int x);
};

#endif
