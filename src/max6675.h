// this library is public domain. enjoy!
// https://learn.adafruit.com/thermocouple/

#ifndef ADAFRUIT_MAX6675_H
#define ADAFRUIT_MAX6675_H

#include "IEsp32.h"
#include "Identity.h"

#ifdef DEPLOY
#include "Arduino.h"

/**************************************************************************/
/*!
    @brief  Class for communicating with thermocouple sensor
*/
/**************************************************************************/
class MAX6675
{
public:
    MAX6675(int8_t SCLK, int8_t CS, int8_t MISO);

    float readCelsius(void);
    float readFahrenheit(void);

    /*!    @brief  For compatibility with older versions
           @returns Temperature in F or NAN on failure! */
    float readFarenheit(void) { return readFahrenheit(); }

private:
    int8_t sclk, miso, cs;
    uint8_t spiread(void);
};
#else
class MAX6675
{
public:
    MAX6675(uint8_t SCLK, uint8_t CS, uint8_t MISO)
    {
        IEsp32::serial_print("Sensor max6675: SCLK ");
        IEsp32::serial_print((uint16_t)SCLK);
        IEsp32::serial_print(", CS ");
        IEsp32::serial_print((uint16_t)CS);
        IEsp32::serial_print(", MISO ");
        IEsp32::serial_println((uint16_t)MISO);
        cs = CS;
    }

    float readCelsius(void)
    {
        if (cs == IDENT::MAXCS1)
            return 15.2;
        if (cs == IDENT::MAXCS2)
            return 28.4;
        return 0.0;
    }
    ~MAX6675() {}

private:
    uint8_t cs;
};

#endif

#endif
