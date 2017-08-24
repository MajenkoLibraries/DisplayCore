#include <DisplayCore.h>
#include <stdarg.h>

/*! \name Colour handling
 *  These functions are all related to manipulating colours in one way or another.
 */

/**@{*/
/*! Convert RGB to 565 colour
 *  =========================
 *  This function takes an RGB triplet (r, g, b) and converts it into
 *  a 16-bit 565 colour.
 *
 *  Example:
 *
 *      unsigned int yellow = tft.color565(255, 255, 0);
 */
color_t DisplayCore::color565(uint8_t r, uint8_t g, uint8_t b) {
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

/*! Get the 3D colour space of a colour
 *  ===================================
 *  This function converts a 565 colour into a 3D coordinate
 *  in RGB colour space (X, Y, Z).
 *
 *  Example:
 *
 *      point3d color = tft.rgb2xyz(Color::Cyan);
 */
point3d DisplayCore::rgb2xyz(color_t rgb) {
    uint8_t red = rgb >> 11;
    uint8_t green = rgb >> 5 & 0b111111;
    uint8_t blue = rgb & 0b11111;

    point3d xyz;

    red = red << 3;
    green = green << 2;
    blue = blue << 3;

    double r = red / 255.0;
    double g = green / 255.0;
    double b = blue / 255.0;

    if (r > 0.04045) {
        r  = pow(((r + 0.055) / 1.055), 2.4);
    } else {
        r  = r / 12.92;
    }

    if (g > 0.04045) {
        g  = pow(((g + 0.055) / 1.055), 2.4);
    } else {
        g  = g / 12.92;
    }

    if (b > 0.04045) {
        b  = pow(((b + 0.055) / 1.055), 2.4);
    } else {
        b  = b / 12.92;
    }

    r = r * 100.0;
    g = g * 100.0;
    b = b * 100.0;

    xyz.x = r * 0.4124 + g * 0.3576 + b * 0.1805;
    xyz.y = r * 0.2126 + g * 0.7152 + b * 0.0722;
    xyz.z = r * 0.0193 + g * 0.1192 + b * 0.9505;
    return xyz;
}

/*! Convert a 3D colour space point to LAB
 *  ======================================
 *  Calculate the LAB colour space value of a 3D point in
 *  RGB colour space.
 *
 *  Example:
 *
 *      point3d labcolor = tft.xyz2lab(color3d);
 */
point3d DisplayCore::xyz2lab(point3d xyz) {
    point3d lab;

    double x = xyz.x / 100.0;
    double y = xyz.y / 100.0;
    double z = xyz.z / 100.0;
    
    if (x > 0.008856) {
        x = pow(x, 1.0/3.0);
    } else {
        x = (7.787 * x) + (16.0 / 116.0);
    }

    if (y > 0.008856) {
        y = pow(y, 1.0/3.0);
    } else {
        y = (7.787 * y) + (16.0 / 116.0);
    }

    if (z > 0.008856) {
        z = pow(z, 1.0/3.0);
    } else {
        z = (7.787 * z) + (16.0 / 116.0);
    }

    lab.x = (116.0 * y) - 16.0;
    lab.y = 500.0 * (x - y);
    lab.z = 200.0 * (y - z);
    return lab;
}

/*! Calculate the DeltaE between two LAB colours
 *  ============================================
 *  This function takes two LAB colours and calculates
 *  the difference (delta) between them.
 *
 *  Example:
 *
 *      double delta = tft.deltaE(colorA, colorB);
 */
double DisplayCore::deltaE(point3d labA, point3d labB) {
    return sqrt(
        (pow(labA.x - labB.x, 2.0))
        + (pow(labA.y - labB.y, 2.0))
        + (pow(labA.z - labB.z, 2.0))
    );
}

/*! Calculate the orthogonal difference between colours
 *  ===================================================
 *  Two RGB 565 colours are compared and the orthogonal distance
 *  between them (as HSV colours) is calculated.
 *
 *  Example:
 *
 *      unsigned long delta = tft.deltaOrth(Color::Yellow, Color::Orange);
 */
uint32_t DisplayCore::deltaOrth(color_t c1, color_t c2) {
    uint32_t hsv1 = rgb2hsv(c1);
    uint32_t hsv2 = rgb2hsv(c2);

    uint8_t h1 = (hsv1 >> 16) & 0xFF;
    uint8_t h2 = (hsv2 >> 16) & 0xFF;
    uint8_t s1 = (hsv1 >> 8) & 0xFF;
    uint8_t s2 = (hsv2 >> 8) & 0xFF;
    uint8_t v1 = hsv1 & 0xFF;
    uint8_t v2 = hsv2 & 0xFF;

    int32_t hd = h1 - h2;
    int32_t sd = s1 - s2;
    int32_t vd = v1 - v2;

    uint32_t sos = (hd * hd) + (sd * sd) + (vd * vd);
    return sos;
}

/*! Convert a 565 RGB colour to HSV
 *  ===============================
 *  Calculate the HSV values for a 565 16-bit RGB colour.
 *
 *  Example:
 *
 *      unsigned long hsv = tft.rgb2hsv(Color::Green);
 */
uint32_t DisplayCore::rgb2hsv(color_t rgb)
{
    uint8_t r = rgb >> 11;
    uint8_t g = rgb >> 5 & 0b111111;
    uint8_t b = rgb & 0b11111;

    r <<= 3;
    g <<= 2;
    b <<= 3;

    uint8_t h, s, v;

    unsigned char rgbMin, rgbMax;

    rgbMin = r < g ? (r < b ? r : b) : (g < b ? g : b);
    rgbMax = r > g ? (r > b ? r : b) : (g > b ? g : b);

    v = rgbMax;
    if (v == 0)
    {
        h = 0;
        s = 0;
        return (h << 16) | (s << 8) | v;
    }

    s = 255 * long(rgbMax - rgbMin) / v;
    if (s == 0)
    {
        h = 0;
        return (h << 16) | (s << 8) | v;
    }

    if (rgbMax == r)
        h = 0 + 43 * (g - b) / (rgbMax - rgbMin);
    else if (rgbMax == g)
        h = 85 + 43 * (b - r) / (rgbMax - rgbMin);
    else
        h = 171 + 43 * (r - g) / (rgbMax - rgbMin);

    return (h << 16) | (s << 8) | v;
}

color_t DisplayCore::hsv2rgb(uint32_t hsv) {
    int hue = (hsv >> 16) & 0xFF;
    int sat = (hsv >> 8) & 0xFF;
    int val = hsv & 0xFF;
    unsigned int H_accent = hue/43;
    unsigned int bottom = ((255 - sat) * val)>>8;
    unsigned int top = val;
    unsigned char rising  = ((top-bottom)  *(hue%43   )  )  /  43  +  bottom;
    unsigned char falling = ((top-bottom)  *(43-hue%43)  )  /  43  +  bottom;

    int r = 0;
    int g = 0;
    int b = 0;
   
    switch(H_accent) {
        case 0:
                r = top;
                g = rising;
                b = bottom;
        break;
       
        case 1:
                r = falling;
                g = top;
                b = bottom;
        break;
       
        case 2:
                r = bottom;
                g = top;
                b = rising;
        break;
       
        case 3:
                r = bottom;
                g = falling;
                b = top;
        break;
       
        case 4:
                r = rising;
                g = bottom;
                b = top;
        break;
       
        case 5:
                r = top;
                g = bottom;
                b = falling;
        break;
    }
    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;
    if (r < 0) r = 0;
    if (g < 0) g = 0;
    if (b < 0) b = 0;
    return rgb(r, g, b);
}

/*! Mix two colours together
 *  ========================
 *  Returns a new colour that is the mixing of the two provided colours.
 *
 *  Example:
 *
 *      unsigned int yellow = tft.mix(Color::Red, Color::Green);
 */
color_t DisplayCore::mix(color_t a, color_t b, int pct) {
    Color565 col_a;
    Color565 col_b;
    Color565 col_out;
    col_a.value = a;
    col_b.value = b;
    uint32_t temp;
    temp = (((int32_t)col_a.r * (255-pct)) / 255) + (((uint32_t)col_b.r * pct) / 255);
    col_out.r = temp;
    temp = (((int32_t)col_a.g * (255-pct)) / 255) + (((uint32_t)col_b.g * pct) / 255);
    col_out.g = temp;
    temp = (((int32_t)col_a.b * (255-pct)) / 255) + (((uint32_t)col_b.b * pct) / 255);
    col_out.b = temp;
    return col_out.value;
}


uint32_t DisplayCore::color2rgb(color_t rgb) {
    uint8_t red = rgb >> 11;
    uint8_t green = rgb >> 5 & 0b111111;
    uint8_t blue = rgb & 0b11111;

    red = red << 3;
    green = green << 2;
    blue = blue << 3;

    return (red << 16) | (green << 8) | (blue);
}

/**@}*/

