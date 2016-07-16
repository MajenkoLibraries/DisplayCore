#include <DisplayCore.h>
#include <stdarg.h>

#include "static3d.h"
#include "quicksort.h"

point3d Scene::translatePoint(point3d p) {
    point3d d;
    d.x = cos(_camang.y*PI/180) * ( sin(_camang.z*PI/180) * (p.y - _camera.y) + cos(_camang.z*PI/180) *
             (p.x - _camera.x) ) - sin(_camang.y*PI/180) * (p.z - _camera.z);
    d.y = sin(_camang.x*PI/180) * ( cos(_camang.y*PI/180) * (p.z - _camera.z) + sin(_camang.y*PI/180) *
             (sin(_camang.z*PI/180) * (p.y - _camera.y) + cos(_camang.z*PI/180) * (p.x - _camera.x)) ) +
             cos(_camang.x*PI/180) * ( cos(_camang.z*PI/180) * (p.y - _camera.y) - sin(_camang.z*PI/180) * (p.x - _camera.x) );
    d.z = cos(_camang.x*PI/180) * ( cos(_camang.y*PI/180) * (p.z - _camera.z) + sin(_camang.y*PI/180) *
             (sin(_camang.z*PI/180) * (p.y - _camera.y) + cos(_camang.z*PI/180) * (p.x - _camera.x)) ) -
             sin(_camang.x*PI/180) * ( cos(_camang.z*PI/180) * (p.y - _camera.y) - sin(_camang.z*PI/180) * (p.x - _camera.x) );
    
    return d;
}
int Scene::render(DisplayCore *dev) {
    // Storage for the translated triangles
    triangle conv[_numtriangles];
    // First tweak the colours in the static scene
    for (int i = 0; i < _numtriangles; i++) {
        conv[i].a.x = _triangles[i].a.x;
        conv[i].a.y = _triangles[i].a.y;
        conv[i].a.z = _triangles[i].a.z;
        conv[i].b.x = _triangles[i].b.x;
        conv[i].b.y = _triangles[i].b.y;
        conv[i].b.z = _triangles[i].b.z;
        conv[i].c.x = _triangles[i].c.x;
        conv[i].c.y = _triangles[i].c.y;
        conv[i].c.z = _triangles[i].c.z;
        conv[i].color = _triangles[i].color;
        conv[i].flags = _triangles[i].flags;
        if (conv[i].flags & TRIANGLE_HIDDEN) {
            continue;
        }
        point3d norm = triangleNormal(conv[i]).norm();
        point3d centroid(
            (conv[i].a.x + conv[i].b.x, conv[i].c.x)/3.0,
            (conv[i].a.y + conv[i].b.y, conv[i].c.y)/3.0,
            (conv[i].a.z + conv[i].b.z, conv[i].c.z)/3.0
        );
        point3d lvec = centroid - _light;
        point3d cvec = centroid - _camera;
        point3d lightnorm = lvec.norm();
        point3d camnorm = cvec.norm();

        double cosphi = 0 - norm.dot(lightnorm);
        double cam_cosphi = norm.dot(camnorm); //camnorm.dot(norm);

        conv[i].flags &= ~TRIANGLE_HIDDEN;

        if (cam_cosphi > 0.1) { // Can't see it, it's backwards!
            conv[i].flags |= TRIANGLE_HIDDEN;
            continue;
        }

        cosphi = _ambient + (cosphi * (1 - _ambient));

        if (cosphi < 0) cosphi = 0;
        if (cosphi > 1) cosphi = 1;

        color_t col = conv[i].color;
        int red = col >> 11;
        int green = col >> 5 & 0b111111;
        int blue = col & 0b11111;

        red <<= 3;
        green <<= 2;
        blue <<= 3;

        red = (double)red * cosphi;
        green = (double)green * cosphi;
        blue = (double)blue * cosphi;

        if (red < 0) red = 0;
        if (red > 255) red = 255;

        if (green < 0) green = 0;
        if (green> 255) green = 255;

        if (blue < 0) blue = 0;
        if (blue > 255) blue = 255;

        conv[i].color = rgb(red, green, blue);
    }


    // Translate all the triangles
    for (int i = 0; i < _numtriangles; i++) {
        if (conv[i].flags & TRIANGLE_HIDDEN) {
            continue;
        }
        conv[i].a = translatePoint(conv[i].a);
        conv[i].b = translatePoint(conv[i].b);
        conv[i].c = translatePoint(conv[i].c);
        // If any points are behind me (or in me) then don't show it.
        if (conv[i].a.z >= 0 || conv[i].b.z >= 0 || conv[i].c.z >= 0) {
            conv[i].flags |= TRIANGLE_HIDDEN;
        }
    }

    // Now sort them from back to front.


    qsval = 0;
    quicksort(conv, 0, _numtriangles-1);
    // Now draw them from the back to the front.

    int rend = 0;

    for (int i = 0; i < _numtriangles; i++) {
        if ((conv[i].flags & TRIANGLE_HIDDEN) == 0) {
            rend++;
            point2d a = dev->map3Dto2D(conv[i].a);
            point2d b = dev->map3Dto2D(conv[i].b);
            point2d c = dev->map3Dto2D(conv[i].c);
            point2d tri[3] = {a, b, c};
            if (_wireframe) {
                dev->drawPolygon(tri, 3, conv[i].color);
            } else {
                dev->fillPolygon(tri, 3, conv[i].color);
            }
        }
    }
    return rend;
}

void Scene::setWireFrame(bool b) {
    _wireframe = b;
}

extern bool rayTriangleIntersect(
    const point3d &orig, const point3d &dir,
    const point3d &v0, const point3d &v1, const point3d &v2,
    float &t, float &u, float &v);

const float err = 0.0001;

static int findTrianglesAround(point3d &p, triangle *tris, int num) {
    for (int i = 0; i < num; i++) {
        tris[i].flags &= ~TRIANGLE_FOUND;
    }
    int nf = 0;
    for (int i = 0; i < num; i++) {
        float dax = fabs(p.x - tris[i].a.x);
        float day = fabs(p.y - tris[i].a.y);
        float daz = fabs(p.z - tris[i].a.z);
        float da = dax + day + daz;
        if (da <= err) {
            tris[i].flags |= TRIANGLE_FOUND;
            nf++;
            continue;
        }
        
        float dbx = fabs(p.x - tris[i].b.x);
        float dby = fabs(p.y - tris[i].b.y);
        float dbz = fabs(p.z - tris[i].b.z);
        float db = dbx + dby + dbz;
        if (db <= err) {
            tris[i].flags |= TRIANGLE_FOUND;
            nf++;
            continue;
        }
        
        float dcx = fabs(p.x - tris[i].c.x);
        float dcy = fabs(p.y - tris[i].c.y);
        float dcz = fabs(p.z - tris[i].c.z);
        float dc = dcx + dcy + dcz;
        if (dc <= err) {
            tris[i].flags |= TRIANGLE_FOUND;
            nf++;
            continue;
        }
    }
    return nf;
}
        
void Scene::trace(DisplayCore *dev, float depth, bool smooth) {
    // Storage for the translated triangles
    triangle conv[_numtriangles];
    for (int i = 0; i < _numtriangles; i++) {
        conv[i].a.x = _triangles[i].a.x;
        conv[i].a.y = _triangles[i].a.y;
        conv[i].a.z = _triangles[i].a.z;
        conv[i].b.x = _triangles[i].b.x;
        conv[i].b.y = _triangles[i].b.y;
        conv[i].b.z = _triangles[i].b.z;
        conv[i].c.x = _triangles[i].c.x;
        conv[i].c.y = _triangles[i].c.y;
        conv[i].c.z = _triangles[i].c.z;
        conv[i].color = _triangles[i].color;
        conv[i].flags = _triangles[i].flags;
        point3d norm = triangleNormal(conv[i]).norm();
        point3d centroid(
            (conv[i].a.x + conv[i].b.x, conv[i].c.x)/3.0,
            (conv[i].a.y + conv[i].b.y, conv[i].c.y)/3.0,
            (conv[i].a.z + conv[i].b.z, conv[i].c.z)/3.0
        );
        point3d lvec = centroid - _light;
        point3d lightnorm = lvec.norm();

        double cosphi = 0 - norm.dot(lightnorm);

        cosphi = _ambient + (cosphi * (1 - _ambient));

        if (cosphi < 0) cosphi = 0;
        if (cosphi > 1) cosphi = 1;

        color_t col = conv[i].color;
        int red = col >> 11;
        int green = col >> 5 & 0b111111;
        int blue = col & 0b11111;

        red <<= 3;
        green <<= 2;
        blue <<= 3;

        red = (double)red * cosphi;
        green = (double)green * cosphi;
        blue = (double)blue * cosphi;

        if (red < 0) red = 0;
        if (red > 255) red = 255;

        if (green < 0) green = 0;
        if (green> 255) green = 255;

        if (blue < 0) blue = 0;
        if (blue > 255) blue = 255;

        conv[i].color = rgb(red, green, blue);
    }

    // Translate all the triangles
    for (int i = 0; i < _numtriangles; i++) {
        conv[i].a = translatePoint(conv[i].a);
        conv[i].b = translatePoint(conv[i].b);
        conv[i].c = translatePoint(conv[i].c);
    }

    // Now sort them from back to front.

//    qsval = 0;
//    quicksort(conv, 0, _numtriangles-1);

    uint32_t width = dev->getWidth();
    uint32_t height = dev->getHeight();

    float fov = dev->getFOV();
    float scale = tan(deg2rad(fov * 0.5));
    float imageAspectRatio = width / (float)height;
    point3d orig(0, 0, 0);
    for (uint32_t j = 0; j < height; ++j) {
        for (uint32_t i = 0; i < width; ++i) {
            // compute primary ray
            float x = (2 * ((width - i - 1) + 0.5) / (float)width - 1) * imageAspectRatio * scale;
            float y = (1 - 2 * (j + 0.5) / (float)height) * scale;
            point3d dir(x, y, depth);
            dir = dir.norm();
            float t, u, v;

            float tm, um, vm;
            tm = 9999999999999999999.99999999;
            int got = -1;
            for (int n = _numtriangles-1; n >= 0; n--) {
                if (rayTriangleIntersect(orig, dir, conv[n].a, conv[n].b, conv[n].c, t, u, v)) {
                    if (t < tm) {
                        tm = t;
                        um = u;
                        vm = v;
                        got = n;
                    }
                }
            }
            if (got >= 0) {

                if (smooth) {
                    float ra = 0;
                    float ga = 0;
                    float ba = 0;
                    int nf = findTrianglesAround(conv[got].a, conv, _numtriangles);
                    for (int i = 0; i < _numtriangles; i++) {
                        if (conv[i].flags & TRIANGLE_FOUND) {
                            color_t col = conv[i].color;
                            int red = col >> 11;
                            int green = col >> 5 & 0b111111;
                            int blue = col & 0b11111;

                            red <<= 3;
                            green <<= 2;
                            blue <<= 3;
                            
                            ra += red;
                            ga += green;
                            ba += blue;
                        }
                    }
                    ra /= nf;
                    ga /= nf;
                    ba /= nf;

                    float rb = 0;
                    float gb = 0;
                    float bb = 0;
                    nf = findTrianglesAround(conv[got].b, conv, _numtriangles);
                    for (int i = 0; i < _numtriangles; i++) {
                        if (conv[i].flags & TRIANGLE_FOUND) {
                            color_t col = conv[i].color;
                            int red = col >> 11;
                            int green = col >> 5 & 0b111111;
                            int blue = col & 0b11111;

                            red <<= 3;
                            green <<= 2;
                            blue <<= 3;
                            
                            rb += red;
                            gb += green;
                            bb += blue;
                        }
                    }
                    rb /= nf;
                    gb /= nf;
                    bb /= nf;

                    float rc = 0;
                    float gc = 0;
                    float bc = 0;
                    nf = findTrianglesAround(conv[got].c, conv, _numtriangles);
                    for (int i = 0; i < _numtriangles; i++) {
                        if (conv[i].flags & TRIANGLE_FOUND) {
                            color_t col = conv[i].color;
                            int red = col >> 11;
                            int green = col >> 5 & 0b111111;
                            int blue = col & 0b11111;

                            red <<= 3;
                            green <<= 2;
                            blue <<= 3;
                            
                            rc += red;
                            gc += green;
                            bc += blue;
                        }
                    }
                    rc /= nf;
                    gc /= nf;
                    bc /= nf;

                    color_t clr = rgb(
                        um * rb + vm * rc + (1 - um - vm) * ra,
                        um * gb + vm * gc + (1 - um - vm) * ga,
                        um * bb + vm * bc + (1 - um - vm) * ba);

                    dev->setPixel(i, j, clr);
                } else {
                    dev->setPixel(i, j, conv[got].color);
                }
            }
        }
    }
}
