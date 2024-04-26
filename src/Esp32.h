#ifndef __ESP32
#define __ESP32

#include "Main.h"

#ifndef DEPLOY
    #include <stdint.h>
    #include <string.h>
    #include <iostream>
#endif

class Esp32
{
    public:

        //
        //*************************  Serial debug  *****************************
        //
        template <class TipodatoSerial>     
        static inline void serial_print(const TipodatoSerial text)
        {
    #ifdef DEPLOY
            Serial.print(text);
    #else
            std::cout << text;
    #endif
        }

        template <class TipodatoSerial>     
        static inline void serial_println(const TipodatoSerial text)
        {
    #ifdef DEPLOY
            Serial.println(text);
    #else
            std::cout << text << std::endl;
    #endif
        }
};


#endif