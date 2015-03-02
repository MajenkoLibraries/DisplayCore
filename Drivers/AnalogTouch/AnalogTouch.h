#ifndef _ANALOGTOUCH_H
#define _ANALOGTOUCH_H

#include <DisplayCore.h>

#if !defined(max)
#define max(A,B) ((A) > (B) ? (A) : (B))
#endif

class AnalogTouch : public Touch {
    private:
        static const uint8_t ANALOGTOUCH_SMPSIZE = 50;

    public: 
        AnalogTouch(uint8_t xl, uint8_t xr, uint8_t yu, uint8_t yd, uint16_t w, uint16_t h) : Touch(w, h), 
            _xl(xl), _xr(xr), _yu(yu), _yd(yd) {}

        void sample();
        int getSample(uint8_t);
        uint16_t x();
        uint16_t y();
        boolean isPressed();

        void initializeDevice();

        uint16_t pressure();

        void setRotation(uint8_t r);

    private:
        struct coord _pos;
        boolean _pressed;
        uint8_t _xl;
        uint8_t _xr;
        uint8_t _yu;
        uint8_t _yd;
        float _scale_x;
        float _scale_y;
        int16_t _offset_x;
        int16_t _offset_y;
        uint16_t _pressure;
        uint8_t _rotation;
};

#endif

