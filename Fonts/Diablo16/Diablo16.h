#ifndef _DIABLO16_H
#define _DIABLO16_H

#include <DisplayCore.h>

class Diablo16 : public DisplayCore {
    private:

        static const int F_blitComtoDisplay         = 35;
        static const int F_bus_Read8                = -122;
        static const int F_bus_Write8               = -121;
        static const int F_charheight               = 29;
        static const int F_charwidth                = 30;
        static const int F_file_CallFunction        = 25;
        static const int F_file_Close               = -431;
        static const int F_file_Count               = 1;
        static const int F_file_Dir                 = 2;
        static const int F_file_Erase               = 3;
        static const int F_file_Error               = -424;
        static const int F_file_Exec                = 4;
        static const int F_file_Exists              = 5;
        static const int F_file_FindFirst           = 6;
        static const int F_file_FindFirstRet        = 36;
        static const int F_file_FindNext            = -428;
        static const int F_file_FindNextRet         = 37;
        static const int F_file_GetC                = -441;
        static const int F_file_GetS                = 7;
        static const int F_file_GetW                = -443;
        static const int F_file_Image               = -438;
        static const int F_file_Index               = -434;
        static const int F_file_LoadFunction        = 8;
        static const int F_file_LoadImageControl    = 9;
        static const int F_file_Mount               = -452;
        static const int F_file_Open                = 10;
        static const int F_file_PlayWAV             = 11;
        static const int F_file_PutC                = 31;
        static const int F_file_PutS                = 32;
        static const int F_file_PutW                = -442;
        static const int F_file_Read                = 12;
        static const int F_file_Rewind              = -447;
        static const int F_file_Run                 = 13;
        static const int F_file_ScreenCapture       = -439;
        static const int F_file_Seek                = -433;
        static const int F_file_Size                = 14;
        static const int F_file_Tell                = 15;
        static const int F_file_Unmount             = -453;
        static const int F_file_Write               = 16;
        static const int F_gfx_BevelShadow          = -196;
        static const int F_gfx_BevelWidth           = -195;
        static const int F_gfx_BGcolour             = -184;
        static const int F_gfx_Button               = 17;
        static const int F_gfx_ChangeColour         = -151;
        static const int F_gfx_Circle               = -136;
        static const int F_gfx_CircleFilled         = -137;
        static const int F_gfx_Clipping             = -186;
        static const int F_gfx_ClipWindow           = -150;
        static const int F_gfx_Cls                  = -126;
        static const int F_gfx_Contrast             = -192;
        static const int F_gfx_Ellipse              = -153;
        static const int F_gfx_EllipseFilled        = -154;
        static const int F_gfx_FrameDelay           = -189;
        static const int F_gfx_Get                  = -182;
        static const int F_gfx_GetPixel             = -139;
        static const int F_gfx_Line                 = -131;
        static const int F_gfx_LinePattern          = -193;
        static const int F_gfx_LineTo               = -129;
        static const int F_gfx_MoveTo               = -127;
        static const int F_gfx_Orbit                = 18;
        static const int F_gfx_OutlineColour        = -191;
        static const int F_gfx_Panel                = -161;
        //static const int F_gfx_PenSize            = -183;
        static const int F_gfx_Polygon              = 19;
        static const int F_gfx_PolygonFilled        = 20;
        static const int F_gfx_Polyline             = 21;
        static const int F_gfx_PutPixel             = -138;
        static const int F_gfx_Rectangle            = -134;
        static const int F_gfx_RectangleFilled      = -135;
        static const int F_gfx_ScreenCopyPaste      = -163;
        static const int F_gfx_ScreenMode           = -190;
        static const int F_gfx_Set                  = -125;
        static const int F_gfx_SetClipRegion        = -152;
        static const int F_gfx_Slider               = -162;
        static const int F_gfx_Transparency         = -188;
        static const int F_gfx_TransparentColour    = -187;
        static const int F_gfx_Triangle             = -140;
        static const int F_gfx_TriangleFilled       = -167;
        static const int F_img_ClearAttributes      = -383;
        static const int F_img_Darken               = -377;
        static const int F_img_Disable              = -376;
        static const int F_img_Enable               = -375;
        static const int F_img_GetWord              = -380;
        static const int F_img_Lighten              = -378;
        static const int F_img_SetAttributes        = -382;
        static const int F_img_SetPosition          = -374;
        static const int F_img_SetWord              = -379;
        static const int F_img_Show                 = -381;
        static const int F_img_Touched              = -384;
        static const int F_media_Flush              = -218;
        static const int F_media_Image              = -217;
        static const int F_media_Init               = -219;
        static const int F_media_RdSector           = 22;
        static const int F_media_ReadByte           = -213;
        static const int F_media_ReadWord           = -214;
        static const int F_media_SetAdd             = -209;
        static const int F_media_SetSector          = -210;
        static const int F_media_Video              = -207;
        static const int F_media_VideoFrame         = -208;
        static const int F_media_WriteByte          = -215;
        static const int F_media_WriteWord          = -216;
        static const int F_media_WrSector           = 23;
        static const int F_mem_Free                 = -417;
        static const int F_mem_Heap                 = -418;
        static const int F_peekM                    = 39;
        static const int F_pin_HI                   = -113;
        static const int F_pin_LO                   = -114;
        static const int F_pin_Read                 = -116;
        static const int F_pin_Set                  = -112;
        static const int F_pokeM                    = 40;
        static const int F_putCH                    = -2;
        static const int F_putstr                   = 24;
        static const int F_readString               = 34;
        static const int F_setbaudWait              = 38;
        static const int F_snd_BufSize              = -461;
        static const int F_snd_Continue             = -464;
        static const int F_snd_Pause                = -463;
        static const int F_snd_Pitch                = -460;
        static const int F_snd_Playing              = -465;
        static const int F_snd_Stop                 = -462;
        static const int F_snd_Volume               = -459;
        static const int F_sys_GetModel             = 26;
        static const int F_sys_GetPmmC              = 28;
        static const int F_sys_GetVersion           = 27;
        static const int F_sys_Sleep                = -403;
        static const int F_touch_DetectRegion       = -406;
        static const int F_touch_Get                = -408;
        static const int F_touch_Set                = -407;
        static const int F_txt_Attributes           = -31;
        static const int F_txt_BGcolour             = -19;
        static const int F_txt_Bold                 = -27;
        static const int F_txt_FGcolour             = -18;
        static const int F_txt_FontID               = -20;
        static const int F_txt_Height               = -22;
        static const int F_txt_Inverse              = -29;
        static const int F_txt_Italic               = -28;
        static const int F_txt_MoveCursor           = -16;
        static const int F_txt_Opacity              = -26;
        static const int F_txt_Set                  = -17;
        static const int F_txt_Underline            = -30;
        static const int F_txt_Width                = -21;
        static const int F_txt_Wrap                 = -32;
        static const int F_txt_Xgap                 = -23;
        static const int F_txt_Ygap                 = -24;
        static const int F_writeString              = 33;

        Stream *_dev;
        int _reset;

        int _timeout;

        bool command(const uint16_t *data, int len) {
            for (int i = 0; i < len; i++) {
                _dev->write((uint8_t)((data[i] >> 8) & 0xFF));
                _dev->write((uint8_t)(data[i] & 0xFF));
            }

            uint32_t start = millis();
            while (millis() - start < _timeout) {
                if (_dev->available()) {
                    if (_dev->read() == 6) {
                        return true;
                    }
                }
            }
            return false;
        }

    public:
        Diablo16(Stream *s, int reset = -1) : _dev(s), _reset(reset), _timeout(10) {}
        Diablo16(Stream &s, int reset = -1) : _dev(&s), _reset(reset), _timeout(10) {}

        void setPixel(int x, int y, color_t c);

        void initializeDevice();

    
        // Dummy functions - not supported
        void invertDisplay(boolean i) {}
        void displayOn() {}
        void displayOff() {}
        void setRotation(int r) {}
    
};

#endif
