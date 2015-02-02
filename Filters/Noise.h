#ifndef _FILTER_NOISE_H_
#define _FILTER_NOISE_H_

#include <Filters.h>

class Noise : public Filter {
    private:
        uint16_t _n;
    public:
        Noise() : Filter(), _n(0) {};
        Noise(uint16_t n) : Filter(), _n(n) {};
        uint16_t function(uint16_t);
        void setLevel(uint16_t n) { _n = n; };
};

#endif
