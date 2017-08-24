#ifndef _FILTER_NOISE_H
#define _FILTER_NOISE_H

#include <Filters.h>

class Noise : public Filter {
    private:
        int _n;
    public:
        Noise() : Filter(), _n(0) {};
        Noise(int n) : Filter(), _n(n) {};
        color_t function(color_t);
        void setLevel(int n) { _n = n; };
};

#endif
