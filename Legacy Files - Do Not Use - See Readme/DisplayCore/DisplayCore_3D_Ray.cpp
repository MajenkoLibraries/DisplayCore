#include <DisplayCore.h>
#include <stdarg.h>

#include "static3d.h"

bool intersect3D_RayTriangle(ray R, triangle T, point3d *I) {
    point3d    u, v, n;              // triangle vectors
    point3d    dir, w0, w;           // ray vectors
    double     r, a, b;              // params to calc ray-plane intersect

    // get triangle edge vectors and plane normal
    u = T.b - T.a;
    v = T.c - T.a;
    n = u * v;


    n.x = u.y * v.z - u.z * v.x;
    n.y = u.z * v.x - u.x * v.z;
    n.z = u.x * v.y - u.y * v.x;


    if (n.x == 0 && n.y == 0 && n.z == 0)
        return false;                  // do not deal with this case

    dir = R.b - R.a;              // ray direction vector
    w0 = R.a - T.a;
    a = -n.dot(w0);
    b = n.dot(dir);
    if (fabs(b) < 0.000001) {     // ray is  parallel to triangle plane
        if (a == 0)                 // ray lies in triangle plane
            return true;
        else return false;              // ray disjoint from plane
    }

    // get intersect point of ray with triangle plane
    r = a / b;
    if (r < 0.0)                    // ray goes away from triangle
        return false;                   // => no intersect
    // for a segment, also test if (r > 1.0) => no intersect

    *I = dir * r + R.a;            // intersect point of ray and plane

    // is I inside T?
    double    uu, uv, vv, wu, wv, D;
    uu = u.dot(u);
    uv = u.dot(v);
    vv = v.dot(v);
    w = *I - T.a;
    wu = w.dot(u);
    wv = w.dot(v);
    D = uv * uv - uu * vv;

    // get and test parametric coords
    double s, t;
    s = (uv * wv - vv * wu) / D;
    if (s < 0.0 || s > 1.0)         // I is outside T
        return false;
    t = (uv * wu - uu * wv) / D;
    if (t < 0.0 || (s + t) > 1.0)  // I is outside T
        return false;

    return true;                       // I is in T
}


static const float kEpsilon = 1e-8;

#define MOLLER_TRUMBORE
#define CULLING

bool rayTriangleIntersect(
    const point3d &orig, const point3d &dir,
    const point3d &v0, const point3d &v1, const point3d &v2,
    float &t, float &u, float &v)
{
#ifdef MOLLER_TRUMBORE
    point3d v0v1 = v1 - v0;
    point3d v0v2 = v2 - v0;
    point3d pvec = dir * v0v2;
    float det = v0v1.dot(pvec);
#ifdef CULLING
    // if the determinant is negative the triangle is backfacing
    // if the determinant is close to 0, the ray misses the triangle
    if (det < kEpsilon) return false;
#else
    // ray and triangle are parallel if det is close to 0
    if (fabs(det) < kEpsilon) return false;
#endif
    float invDet = 1 / det;

    point3d tvec = orig - v0;
    u = tvec.dot(pvec) * invDet;
    if (u < 0 || u > 1) return false;

    point3d qvec = tvec * v0v1;
    v = dir.dot(qvec) * invDet;
    if (v < 0 || u + v > 1) return false;
    
    t = v0v2.dot(qvec) * invDet;
    
    return true;
#else
    // compute plane's normal
    point3d v0v1 = v1 - v0;
    point3d v0v2 = v2 - v0;
    // no need to normalize
    point3d N = v0v1 * v0v2; // N
    float denom = N.dot(N);
    
    // Step 1: finding P
    
    // check if ray and plane are parallel ?
    float NdotRayDirection = N.dot(dir);
    if (fabs(NdotRayDirection) < kEpsilon) // almost 0
        return false; // they are parallel so they don't intersect ! 

    // compute d parameter using equation 2
    float d = N.dot(v0);
    
    // compute t (equation 3)
    t = (N.dot(orig) + d) / NdotRayDirection;
    // check if the triangle is in behind the ray
    if (t < 0) return false; // the triangle is behind
 
    // compute the intersection point using equation 1
    point3d P = orig + dir * t;
 
    // Step 2: inside-outside test
    point3d C; // vector perpendicular to triangle's plane
 
    // edge 0
    point3d edge0 = v1 - v0; 
    point3d vp0 = P - v0;
    C = edge0 * vp0;
    if (N.dot(C) < 0) return false; // P is on the right side
 
    // edge 1
    point3d edge1 = v2 - v1; 
    point3d vp1 = P - v1;
    C = edge1 * vp1;
    if ((u = N.dot(C)) < 0)  return false; // P is on the right side
 
    // edge 2
    point3d edge2 = v0 - v2; 
    point3d vp2 = P - v2;
    C = edge2 * vp2;
    if ((v = N.dot(C)) < 0) return false; // P is on the right side;

    u /= denom;
    v /= denom;

    return true; // this ray hits the triangle
#endif
}

#define RAND (((random() % 1000) - 500) / 500.0)
/*
int main(int argc, char **argv)
{
    point3d v0(0, 1, -5);
    point3d v1(RAND, RAND, RAND);
    point3d v2(RAND, RAND, RAND);

    const uint32_t width = 640;
    const uint32_t height = 480;
    point3d cols[3] = {{0.6, 0.4, 0.1}, {0.1, 0.5, 0.3}, {0.1, 0.3, 0.7}};
    point3d *framebuffer = new point3d[width * height];
    point3d *pix = framebuffer;
    float fov = 51.52;
    float scale = tan(deg2rad(fov * 0.5));
    float imageAspectRatio = width / (float)height;
    point3d orig(0);
    for (uint32_t j = 0; j < height; ++j) {
        for (uint32_t i = 0; i < width; ++i) {
            // compute primary ray
            float x = (2 * (i + 0.5) / (float)width - 1) * imageAspectRatio * scale;
            float y = (1 - 2 * (j + 0.5) / (float)height) * scale;
            point3d dir(x, y, -1);
            dir.normalize();
            float t, u, v;
            if (rayTriangleIntersect(orig, dir, v0, v1, v2, t, u, v)) {
                // [comment]
                // Interpolate colors using the barycentric coordinates
                // [/comment]
                *pix = u * cols[0] + v * cols[1] + (1 - u - v) * cols[2];
                // uncomment this line if you want to visualize the row barycentric coordinates
                //*pix = point3d(u, v, 1 - u - v);
            }
            pix++;
        }
    }
    
    // Save result to a PPM image (keep these flags if you compile under Windows)
    std::ofstream ofs("./out.ppm", std::ios::out | std::ios::binary);
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for (uint32_t i = 0; i < height * width; ++i) {
        char r = (char)(255 * clamp(0, 1, framebuffer[i].x));
        char g = (char)(255 * clamp(0, 1, framebuffer[i].y));
        char b = (char)(255 * clamp(0, 1, framebuffer[i].z));
        ofs << r << g << b;
    }

    ofs.close();

    delete [] framebuffer;

    return 0;
}
*/
