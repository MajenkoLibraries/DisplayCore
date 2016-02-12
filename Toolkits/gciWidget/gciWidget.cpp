#include <gciWidget.h>

static inline uint16_t swaple(uint16_t be) {
	return ((be & 0xFF00) >> 8) | ((be & 0x00FF) << 8);
}

void gciWidget::load() {
    if (_loaded) {
        return;
    }

    File f;
    char temp[strlen(_filename) + 5];
    sprintf(temp, "%s.dat", _filename);

    char line[80];
    int lpos = 0;

    if (f = SD.open(temp)) {
        while (f.available()) {
            char inch = f.read();
            if (inch == '\r') continue;
            if (inch == '\n') {
                lpos = 0;
                if (line[0] != '"') {
                    continue;
                }

                char *name = strtok(line, " ");
                char *low = strtok(NULL, " ");
                char *high = strtok(NULL, " ");
                char *xpos = strtok(NULL, " ");
                char *ypos = strtok(NULL, " ");
                if (ypos == NULL) {
                    continue;
                }
                while (*name == '"') {
                    name++;
                }
                while (name[strlen(name) - 1] == '"') {
                    name[strlen(name) - 1] = 0;
                }
                if (strcmp(name, _widgetname) != 0) {
                    continue;
                }
                _offset = strtol(high, NULL, 16) << 16 | strtol(low, NULL, 16);
                _x = strtol(xpos, NULL, 16);
                _y = strtol(ypos, NULL, 16);
                break;
            }
            if (lpos >= 75) {
                continue;
            }
            line[lpos++] = inch;
            line[lpos] = 0;
        }
        f.close();

        sprintf(temp, "%s.gci", _filename);
        if (f = SD.open(temp)) {
            f.seek(_offset);
            f.read(&_header, sizeof(struct gcihdr));
            f.close();
            _sense_x = 0;
            _sense_y = 0;
            _sense_w = swaple(_header.width);
            _sense_h = swaple(_header.height);
        }
        
 
    }
    _loaded = true;
}

void gciWidget::draw(DisplayCore *dev, int16_t x, int16_t y) {
    File f;
    load();
    char temp[strlen(_filename) + 5];
    sprintf(temp, "%s.gci", _filename);

    int framesize = _sense_w * _sense_h;

    if (f = SD.open(temp)) {
        f.seek(_offset + sizeof(struct gcihdr) + (framesize * getValue() * 2));
        dev->openWindow(_x, _y, _sense_w, _sense_h);
        uint32_t done = 0;
        uint16_t buf[IMG_BUFSZ];
        while (done < framesize) {
            int chunk = framesize - done;
            if (chunk > IMG_BUFSZ) chunk = IMG_BUFSZ;				
            f.read(buf, chunk * 2);
            for (int j = 0; j < chunk; j++) {
                dev->windowData(swaple(buf[j]));
            }
            done += chunk;
        }
        dev->closeWindow();
    }
    f.close();
}

uint32_t gciWidget::getFrames() {
    load();
    return swaple(_header.frames);
}

void gciWidget::setValue(uint16_t x) {
    if (x >= getFrames()) {
        x = getFrames() - 1;
    }
    _value = x;
    _redraw = true;
}
