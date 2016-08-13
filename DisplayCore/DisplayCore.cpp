#include <DisplayCore.h>
#include <stdarg.h>

DisplayCore::DisplayCore() {
    cursor_y = cursor_x = 0;
    textcolor = 0xFFFF;
    textbgcolor = 0;
    wrap = true;
    font = Fonts::Default;
}
