#ifndef _ADAFRUIT_ST7789H_
#define _ADAFRUIT_ST7789H_

#include "../lib/Adafruit_ST7735_RK/src/Adafruit_ST77xx.h"

/// Subclass of ST77XX type display for ST7789 TFT Driver
class Adafruit_ST7789 : public Adafruit_ST77xx {
  public:
    Adafruit_ST7789(int8_t cs, int8_t dc, int8_t mosi, int8_t sclk,
      int8_t rst = -1);
    Adafruit_ST7789(int8_t cs, int8_t dc, int8_t rst);
    Adafruit_ST7789(SPIClass *spiClass, int8_t cs, int8_t dc, int8_t rst);

#ifdef SYSTEM_VERSION_v151RC1
  // In 1.5.0-rc.1, SPI interfaces are handled differently. You can still pass in SPI, SPI1, etc.
	// but the code to handle it varies
  Adafruit_ST7789(::particle::SpiProxy<HAL_SPI_INTERFACE1> *spiProxy, int8_t cs, int8_t dc, int8_t rst) : 
    Adafruit_ST7789(&spiProxy->instance(), cs, dc, rst) {};

#if Wiring_SPI1
  Adafruit_ST7789(::particle::SpiProxy<HAL_SPI_INTERFACE2> *spiProxy, int8_t cs, int8_t dc, int8_t rst) : 
    Adafruit_ST7789(&spiProxy->instance(), cs, dc, rst) {};
#endif

#if Wiring_SPI2
  Adafruit_ST7789(::particle::SpiProxy<HAL_SPI_INTERFACE3> *spiProxy, int8_t cs, int8_t dc, int8_t rst) : 
    Adafruit_ST7789(&spiProxy->instance(), cs, dc, rst) {};
#endif

#endif /* SYSTEM_VERSION_v151RC1 */

    void setRotation(uint8_t m);
    void init(uint16_t width, uint16_t height);
};

#endif // _ADAFRUIT_ST7789H_
