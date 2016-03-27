#ifndef _XPT2046_H
#define _XPT2046_H

#include <DisplayCore.h>
#include <DSPI.h>

class XPT2046 : public Touch {
    private:
        static const uint8_t TOUCH_CMD_X      = 0xD0;
        static const uint8_t TOUCH_CMD_Y      = 0x90;
        static const uint8_t XPT2046_SMPSIZE  = 50;

    public: 
        /**@{*/
        /*! Create a new XPT2046 object
         *  ===========================
         *  This creates a new XPT2046 touchscreen object.  It requires an SPI compatible TFTCommunicator driver to be passed
         *  either as a pointer or as a reference.  It also requires the width and height (natural orientation) of the touch screen.
         *
         *  Example:
         *
         *      XPT2046 ts(spiDev, 240, 320);
         */
        XPT2046(DSPI *spi, uint8_t cs, int w, int h) : Touch(w, h), _spi(spi), _cs(cs)  {}
        XPT2046(DSPI &spi, uint8_t cs, int w, int h) : Touch(w, h), _spi(&spi), _cs(cs)  {}
        /**@}*/

        void sample();
        int x();
        int y();
        boolean isPressed();

        void initializeDevice();

        void setRotation(int r);

    private:
        struct coord pos;
        boolean pressed;
        int _rotation;
        DSPI *_spi;
        uint8_t _cs;

        int getSample(uint8_t pin);

};

#endif

