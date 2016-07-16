#ifndef _STATIC_3D_H
#define _STATIC_3D_H

static inline float deg2rad(const float &deg) { return deg * M_PI / 180; }
static inline float clamp(const float &lo, const float &hi, const float &v) { return max(lo, min(hi, v)); }

static inline bool isInsideTriangle(point2d s, point2d a, point2d b, point2d c) {
    int as_x = s.x-a.x;
    int as_y = s.y-a.y;

    bool s_ab = (b.x-a.x)*as_y-(b.y-a.y)*as_x > 0;

    if((c.x-a.x)*as_y-(c.y-a.y)*as_x > 0 == s_ab) return false;

    if((c.x-b.x)*(s.y-b.y)-(c.y-b.y)*(s.x-b.x) > 0 != s_ab) return false;

    return true;
}

static inline point3d triangleNormal(triangle t) {
    point3d pba = t.b - t.a;
    point3d pca = t.c - t.a;
    return pba * pca;
}

static inline double zentroid(triangle *t) {
    return (t->a.z + t->b.z + t->c.z) / 3.0;
}

#endif
