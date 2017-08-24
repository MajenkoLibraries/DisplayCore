#ifndef _SCREENDUMP_H
#define _SCREENDUMP_H

#include <DisplayCore.h>
#include <SD.h>

class ScreenDump {
    public:
        static void dump565(DisplayCore &dev, SDClass &sd, const char *filename);
        static void dumpBMP(DisplayCore &dev, SDClass &sd, const char *filename);
};

#endif
