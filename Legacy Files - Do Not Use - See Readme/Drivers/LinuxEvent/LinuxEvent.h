#ifndef _LINUXEVENT_H
#define _LINUXEVENT_H

#include <DisplayCore.h>
#include <CircularBuffer.h>

#include <sys/time.h>
#include <sys/select.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#define KEY_ESC     1
#define KEY_1       2
#define KEY_2       3
#define KEY_3       4
#define KEY_4       5
#define KEY_5       6
#define KEY_6       7
#define KEY_7       8
#define KEY_8       9
#define KEY_9       10
#define KEY_0       11
#define KEY_MINUS   12
#define KEY_EQUALS  13
#define KEY_BS      14
#define KEY_TAB     15
#define KEY_Q       16
#define KEY_W       17
#define KEY_E       18
#define KEY_R       19
#define KEY_T       20
#define KEY_Y       21
#define KEY_U       22
#define KEY_I       23
#define KEY_O       24
#define KEY_P       25
#define KEY_BRKOP   26
#define KEY_BRKCL   27
#define KEY_RETURN  28
#define KEY_LCTRL   29
#define KEY_A       30
#define KEY_S       31
#define KEY_D       32
#define KEY_F       33
#define KEY_G       34
#define KEY_H       35
#define KEY_J       36
#define KEY_K       37
#define KEY_L       38
#define KEY_SEMICOL 39
#define KEY_QUOTE   40
#define KEY_BQUOTE  41
#define KEY_LSHIFT  42
#define KEY_HASH    43
#define KEY_Z       44
#define KEY_X       45
#define KEY_C       46
#define KEY_V       47
#define KEY_B       48
#define KEY_N       49
#define KEY_M       50
#define KEY_COMMA   51
#define KEY_DOT     52
#define KEY_SLASH   53
#define KEY_RSHIFT  54
#define KEY_KPSTAR  55
#define KEY_LALT    56
#define KEY_SPACE   57
#define KEY_CAPS    58
#define KEY_F1      59
#define KEY_F2      60
#define KEY_F3      61
#define KEY_F4      62
#define KEY_F5      63
#define KEY_F6      64
#define KEY_F7      65
#define KEY_F8      66
#define KEY_F9      67
#define KEY_F10     68
#define KEY_NUMLK   69
#define KEY_SCRLK   70
#define KEY_KP7     71
#define KEY_KP8     72
#define KEY_KP9     73
#define KEY_KPMINUS 74
#define KEY_KP4     75
#define KEY_KP5     76
#define KEY_KP6     77
#define KEY_KPPLUS  78
#define KEY_KP1     79
#define KEY_KP2     80
#define KEY_KP3     81
#define KEY_KP0     82
#define KEY_KPDOT   83
#define KEY_BSLASH  86
#define KEY_F11     87
#define KEY_F12     88
#define KEY_KPENT   96
#define KEY_RCTRL   97
#define KEY_KPSLASH 98
#define KEY_PRTSCR  99
#define KEY_RALT    100
#define KEY_HOME    102
#define KEY_UP      103
#define KEY_PGUP    104
#define KEY_LEFT    105
#define KEY_RIGHT   106
#define KEY_END     107
#define KEY_DOWN    108
#define KEY_PGDN    109
#define KEY_INSERT  110
#define KEY_DELETE  111
#define KEY_MUTE    113
#define KEY_VDOWN   114
#define KEY_VUP     115
#define KEY_PAUSE   119
#define KEY_LWIN    125
#define KEY_RWIN    127
#define KEY_CALC    140
#define KEY_COMP    144
#define KEY_NEXT    163
#define KEY_PLAY    164
#define KEY_PREV    165
#define KEY_STOP    166
#define KEY_MEDIA   171


struct event {
    struct timeval tv;
    unsigned short type;
    unsigned short code;
    unsigned int value;
};

#if !defined(max)
#define max(A,B) ((A) > (B) ? (A) : (B))
#endif

#define _MAX_IN_DEV 10

class LinuxEvent : public Touch, public Stream {
    private:
        CircularBuffer<char> _rxBuffer;

    public: 
        LinuxEvent(int w, int h) : Touch(w, h), _rxBuffer(64) {}


        void sample();
        int getSample(uint8_t);
        int x();
        int y();
        int rawX();
        int rawY();
        boolean isPressed();

        void initializeDevice();

        int pressure();

        void setRotation(int r);
        size_t write(uint8_t v) { return 0; }
        int available() { return _rxBuffer.available(); }
        int read() { return _rxBuffer.read(); }
        int peek() { return 0; }
        void flush() {}

    private:
        int _fd[_MAX_IN_DEV];
        uint32_t _lastChange;
        struct coord _pos;
        boolean _pressed;
        float _scale_x;
        float _scale_y;
        int _offset_x;
        int _offset_y;
        int _rotation;
        int _x;
        int _y;
        int _maxfd;
};

#endif

