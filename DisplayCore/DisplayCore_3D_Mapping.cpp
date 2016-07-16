#include <DisplayCore.h>
#include <stdarg.h>

point2d DisplayCore::map3Dto2D(point3d &d) {
    point2d p2d;

    p2d.x = d.x * _fov / d.z + (getWidth() / 2);
    p2d.y = d.y * _fov / d.z + (getHeight() / 2);

    return p2d;
}
    
