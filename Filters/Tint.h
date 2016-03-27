#ifndef _FILTER_TINT_H
#define _FILTER_TINT_H

#include <Filters.h>

class Tint : public Filter {
    private:
        color_t _c;
    public:
        Tint() : Filter(), _c(Color::Sepia) {};
        Tint(color_t c) : Filter(), _c(c) {};
        color_t function(color_t);
        void setTint(color_t c) { _c = c; };
};

#endif
