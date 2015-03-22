#include <ScreenDump.h>
#include <SD.h>

struct BitmapFileHeader {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfBitmapOffset;
} __attribute__((packed));

struct BitmapInfoHeader {
    uint32_t biSize;
    int32_t  biWidth;
    int32_t  biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t  biXPelsPerMeter;
    int32_t  biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
    uint32_t biMaskRed;
    uint32_t biMaskGreen;
    uint32_t biMaskBlue;
    uint32_t biMaskAlpha;
    uint16_t biCSType;
    uint32_t biRedX;
    uint32_t biRedY;
    uint32_t biRedZ;
    uint32_t biGreenX;
    uint32_t biGreenY;
    uint32_t biGreenZ;
    uint32_t biBlueX;
    uint32_t biBlueY;
    uint32_t biBlueZ;
    uint32_t biGammaRed;
    uint32_t biGammaGreen;
    uint32_t biGammaBlue;
} __attribute__((packed));


void ScreenDump::dump565(DisplayCore &dev, SDClass &sd, const char *filename) {
    File f = sd.open(filename, O_WRITE | O_CREAT);
    for (int y = 0; y < dev.getHeight(); y++) {
        for (int x = 0; x < dev.getWidth(); x++) {
            uint16_t col = dev.colorAt(x, y);
            f.write((uint8_t)(col >> 8));
            f.write((uint8_t)(col & 0xFF));
        }
    }
    f.flush();
    f.close();
}

void ScreenDump::dumpBMP(DisplayCore &dev, SDClass &sd, const char *filename) {
    struct BitmapFileHeader header;
    struct BitmapInfoHeader info;

    uint32_t w = dev.getWidth();
    uint32_t h = dev.getHeight();

    header.bfType = 0x4D42;
    header.bfSize = 138 + ((w*h)*2);
    header.bfReserved1 = 0;
    header.bfReserved2 = 0;
    header.bfBitmapOffset = 138;

    info.biSize = 124;
    info.biWidth = w;
    info.biHeight = h;
    info.biPlanes = 1;
    info.biBitCount = 16;
    info.biCompression = 3;
    info.biSizeImage = ((w*h)*2);
    info.biXPelsPerMeter = 3780;
    info.biYPelsPerMeter = 3780;
    info.biClrUsed = 0;
    info.biClrImportant = 0;
    info.biMaskRed = 0xF800;
    info.biMaskGreen = 0x07E0;
    info.biMaskBlue = 0x001F;
    info.biMaskAlpha = 0;
    info.biCSType = 18242;
    info.biRedX = 29522;
    info.biRedY = 0;
    info.biRedZ = 0;
    info.biGreenX = 0;
    info.biGreenY = 0;
    info.biGreenZ = 0;
    info.biBlueX = 0;
    info.biBlueY = 0;
    info.biBlueZ = 0;
    info.biGammaRed = 0;
    info.biGammaGreen = 0;
    info.biGammaBlue = 0;


    File f = sd.open(filename, O_WRITE | O_CREAT | O_TRUNC);
    f.write((const uint8_t *)&header, sizeof(struct BitmapFileHeader));
    f.write((const uint8_t *)&info, sizeof(struct BitmapInfoHeader));
    for (int i = sizeof(struct BitmapFileHeader) + sizeof(struct BitmapInfoHeader); i < 138; i++) {
        f.write((uint8_t)0);
    }
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            uint16_t col = dev.colorAt(x, h - y - 1);
            f.write((uint8_t)(col >> 8));
            f.write((uint8_t)(col & 0xFF));
        }
    }
    f.flush();
    f.close();
}
