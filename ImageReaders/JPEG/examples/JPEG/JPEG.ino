#include <ILI9481.h>
#include <JPEG.h>

extern const uint8_t logo3_jpg[] asm("_binary_objects_image_jpg_start");
extern const uint8_t logo3_len[] asm("_binary_objects_image_jpg_size");

ILI9481 tft(PINS_8BIT_SHIELD);
JPEG jpeg(logo3_jpg, (uint32_t)&logo3_len);

void setup() {
    tft.initializeDevice();
    tft.fillScreen(Color::Black);
    jpeg.draw(&tft, 0, 0);
    tft.printf("Width: %d Height: %d", jpeg.getWidth(), jpeg.getHeight());
}

void loop() {
    
}
