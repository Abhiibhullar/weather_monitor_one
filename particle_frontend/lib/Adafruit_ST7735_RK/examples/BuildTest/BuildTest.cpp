#include "Adafruit_ST7735.h"
#include "Adafruit_ST7789.h"

// You can't really have two of these on the same pins, but this is just to make sure it compiles
// It's not a working example.
// I've removed the examples because it's not possible to have dependencies for individual examples
// and the necessary libraries won't be included and the build will fail. Since other boards like
// the miniTFTWing have their own examples, you should just test this library with those examples.
Adafruit_ST7735 st7735(&SPI, D2, D3, D4);
Adafruit_ST7789 st7789(&SPI1, D2, D3, D4);

void setup() {

}

void loop() {

}
