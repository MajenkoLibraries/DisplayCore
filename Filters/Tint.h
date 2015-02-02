#ifndef _FILTER_TINT_H_
#define _FILTER_TINT_H_

#include <Filters.h>

class Tint : public Filter {
    private:
        uint16_t _c;
    public:
        Tint() : Filter(), _c(Color::Sepia) {};
        Tint(uint16_t c) : Filter(), _c(c) {};
        uint16_t function(uint16_t);
        void setTint(uint16_t c) { _c = c; };
};

#endif
