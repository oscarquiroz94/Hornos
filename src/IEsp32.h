#ifndef __IESP32
#define __IESP32

#include "Main.h"
#include "Identity.h"

#ifndef DEPLOY
    #include <stdint.h>
    #include <string.h>
    #include <iostream>
    #include "SeriaLib.h"
    #include <chrono>
    #include <thread>
    #include <mutex>
    #include <deque>
    #include <condition_variable>
    extern SeriaLib   serial_nxcom;
#else
    #include <Arduino.h>
#endif

class IEsp32
{
    public:

        //
        //*************************  Serial debug  *****************************
        //  
        static inline void serial_begin(const uint32_t baud)
        {
#ifdef DEPLOY
            Serial.begin(baud);
#endif
        }

        //----------------

        template <class TipodatoSerial>     
        static inline void serial_print(const TipodatoSerial text)
        {
#ifdef DEPLOY
            Serial.print(text);
#else
            std::cout << text;
#endif
        }

        //----------------

        template <class TipodatoSerial>     
        static inline void serial_println(const TipodatoSerial text)
        {
#ifdef DEPLOY
            Serial.println(text);
#else
            std::cout << text << std::endl;
#endif
        }

        //
        //**************************  SERIAL NEXTION  ***************************
        //
        static inline void serial2_begin
        (unsigned long baud, uint32_t config, int8_t rxPin, int8_t txPin)
        {
#ifdef DEPLOY
            Serial2.begin(baud, config, rxPin, txPin); 
#endif
        }

        //---------------

        static inline bool serial2_available()
        {
#ifdef DEPLOY
            return Serial2.available();
#else
            return true;
#endif
        }

        //----------------

        template <class TipodatoSerial>     
        static inline void serial2_print(const TipodatoSerial text)
        {
#ifdef DEPLOY
            Serial2.print(text);
#else
            serial_nxcom.writeString(text);
#ifdef SHOWNEXTION
            std::cout << text << std::endl;
#endif
#endif
        }

        static inline void serial2_write(char v)
        {
#ifdef DEPLOY
            Serial2.write(v);
#ifdef SHOWNEXTION
            static int count = 0;
            count++;
            if (count == 3)
            {
                Serial.println();
                count = 0;
            }
#endif
#elif defined(EMULATION) && defined(EXTERNAL_INTERFACES)
            serial_nxcom.writeChar(v);
#ifdef SHOWNEXTION
            static int count = 0;
            std::cout << v;
            count++;
            if (count == 3)
            {
                printlnDebug();
                count = 0;
            }
#endif  
#endif
        }

        //
        //*************************** PINOUT ********************
        //
        static bool digital_Read(const uint8_t pin)
        {
#ifdef DEPLOY
            return digitalRead(pin);
#else
            return false;
#endif
        }

        //----------------

        static void digital_Write(const uint8_t name, const uint8_t pin, const uint8_t state)
        {
#ifdef DEPLOY
            digitalWrite(pin, state);
#else
#ifdef SHOW_IO
            uint16_t name16 = (uint16_t)name;
            uint16_t pin16 = (uint16_t)pin;
            uint16_t val16 = (uint16_t)state;
            if(name16 == IDENT::OUTVALVULA) {serial_print("Valvula, pin: "); serial_print(pin16); serial_print(" val: "); serial_println(val16);}
            else if(name16 == IDENT::OUTROJA) {serial_print("Baliza roja, pin: "); serial_print(pin16); serial_print(" val: "); serial_println(val16);}
            else if(name16 == IDENT::OUTVERDE) {serial_print("Baliza verde, pin: "); serial_print(pin16); serial_print(" val: "); serial_println(val16);}  
            else if(name16 == IDENT::OUTVENT) {serial_print("Ventilador, pin: "); serial_print(pin16); serial_print(" val: "); serial_println(val16);}
            else if(name16 == IDENT::OUTQUEM) {serial_print("Quemador, pin: "); serial_print(pin16); serial_print(" val: "); serial_println(val16);}
            else {serial_print("*** DIGIWRITE DESCONOCIDO **"); serial_println(name16);}
#endif
#endif
        }

        //-----------------

        static void dac_Write(const uint8_t pin, const uint8_t value)
        {
#ifdef DEPLOY
            return dacWrite(pin, value);
#else
            
#endif
        }


        //******************** DUMMIES *********************
        static inline long str2int(const char* txt)
        {
#ifdef DEPLOY
            return String(txt).toInt();
#else
            return std::stoi(txt);
#endif
        }

        //------------------

        static inline void retardo(const uint16_t t) 
        {
#ifdef DEPLOY
            delay(t);
#else
            std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(t));
#endif
        }
};


#endif