#include <DisplayCore.h>
#include <stdarg.h>

color_t Filter::process(color_t incol) {
    color_t outcol = function(incol);
    if (_next != NULL) {
        return _next->process(outcol);
    }
    return outcol;
}


