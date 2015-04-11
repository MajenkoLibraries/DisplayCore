#ifndef _LINUXEVENT_H
#define _LINUXEVENT_H

#include <DisplayCore.h>

#include <sys/time.h>
#include <sys/select.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>


struct event {
    struct timeval tv;
    unsigned short type;
    unsigned short code;
    unsigned int value;
};

#if !defined(max)
#define max(A,B) ((A) > (B) ? (A) : (B))
#endif

class LinuxEvent : public Touch {

    public: 
        LinuxEvent(const char *dev, uint16_t w, uint16_t h) : Touch(w, h), _name(dev) {}

        void sample();
        int getSample(uint8_t);
        uint16_t x();
        uint16_t y();
        boolean isPressed();

        void initializeDevice();

        uint16_t pressure();

        void setRotation(uint8_t r);

    private:
        int _fd;
        int _devid;
        const char *_name;
        uint32_t _lastChange;
        struct coord _pos;
        boolean _pressed;
        float _scale_x;
        float _scale_y;
        int16_t _offset_x;
        int16_t _offset_y;
        uint8_t _rotation;
        uint16_t _x;
        uint16_t _y;
};

#endif

