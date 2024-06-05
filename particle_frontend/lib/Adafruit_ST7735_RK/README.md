# Adafruit-ST7735-RK

*Port of Adafruit ST7735/ST7789 library for Particle devices*

Ported from [Adafruit-ST7735-Library](https://github.com/adafruit/Adafruit-ST7735-Library), version 1.2.7.

I've removed the examples because it's not possible to have dependencies for individual examples
and the necessary libraries won't be included and the build will fail. Since other boards like
the miniTFTWing have their own examples, you should just test this library with those examples.

You can find the examples in the original library above if you need them.

## Original ReadMe

This is a library for several Adafruit displays based on ST77* drivers.

  Works with the Adafruit 1.8" TFT Breakout w/SD card
    ----> http://www.adafruit.com/products/358
  The 1.8" TFT shield
    ----> https://www.adafruit.com/product/802
  The 1.44" TFT breakout
    ----> https://www.adafruit.com/product/2088
  as well as Adafruit raw 1.8" TFT display
    ----> http://www.adafruit.com/products/618
 
Check out the links above for our tutorials and wiring diagrams.
These displays use SPI to communicate, 4 or 5 pins are required to
interface (RST is optional).

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries.
MIT license, all text above must be included in any redistribution.

Recent Arduino IDE releases include the Library Manager for easy installation. Otherwise, to download, click the DOWNLOAD ZIP button, uncompress and rename the uncompressed folder Adafruit_ST7735. Confirm that the Adafruit_ST7735 folder contains Adafruit_ST7735.cpp, Adafruit_ST7735.h and related source files. Place the Adafruit_ST7735 library folder your ArduinoSketchFolder/Libraries/ folder. You may need to create the Libraries subfolder if its your first library. Restart the IDE.

Also requires the Adafruit_GFX library for Arduino.

# Version History

### 1.2.8 (2020-08-02)

- Upgrade to Adafruit_GFX_RK 1.5.8
