#ifndef _XPT2046_H
#define _XPT2046_H

#include <DisplayCore.h>
#include <DSPI.h>

class XPT2046 : public Touch {
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
        XPT2046(DSPI *spi, uint8_t cs, uint16_t w, uint16_t h) : Touch(w, h), _spi(spi), _cs(cs)  {}
        XPT2046(DSPI &spi, uint8_t cs, uint16_t w, uint16_t h) : Touch(w, h), _spi(&spi), _cs(cs)  {}
        /**@}*/

        void sample();
        uint16_t x();
        uint16_t y();
        boolean isPressed();

        void initializeDevice();

        void setRotation(uint8_t r);

    private:
        struct coord pos;
        boolean pressed;
        uint8_t _rotation;
        DSPI *_spi;
        uint8_t _cs;

        int getSample(uint8_t pin);

};

#endif

