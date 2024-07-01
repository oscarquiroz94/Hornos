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

    #define HIGH   0x1
    #define LOW    0x0
    #define INPUT  0x0
    #define OUTPUT 0x1
    #define INPUT_PULLUP 0x2
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

        static inline bool serial_available()
        {
#ifdef DEPLOY
            return Serial.available();
#else
            return true;
#endif
        }

        //-----------------

        static inline int serial_read()
        {
#ifdef DEPLOY
            return Serial.read();
#else
            return 0;
#endif
        }

        //----------------
        template <class TipodatoSerial> 
        static inline void serial_print_shall(const TipodatoSerial text)
        {
#ifdef DEPLOY
            Serial.print(text);
#else
            std::cout << text;
#endif
        }

        template <class TipodatoSerial>     
        static inline void serial_print(const TipodatoSerial text)
        {
#ifdef DEBUG_INFO
#ifdef DEPLOY
            Serial.print(text);
#else
            std::cout << text;
#endif
#endif
        }

        //----------------

        template <class TipodatoSerial>     
        static inline void serial_println_shall(const TipodatoSerial text)
        {
#ifdef DEPLOY
            Serial.println(text);
#else
            std::cout << text << std::endl;
#endif
        }

        template <class TipodatoSerial>     
        static inline void serial_println(const TipodatoSerial text)
        {
#ifdef DEBUG_INFO
#ifdef DEPLOY
            Serial.println(text);
#else
            std::cout << text << std::endl;
#endif
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

        static inline int serial2_read()
        {
#ifdef DEPLOY
            return Serial2.read();
#else
            return 0;
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
        static bool digital_Read(const uint8_t name, const uint8_t pin)
        {
#ifdef DEPLOY
            bool state = !digitalRead(pin);
#ifdef SHOW_IO
            uint16_t name16 = (uint16_t)name;
            uint16_t pin16 = (uint16_t)pin;
            
            if(name16 == IDENT::INQUEMRUN)       {serial_print_shall("Is Quemador,   pin: "); serial_print_shall(pin16);serial_print_shall(" val: "); serial_println_shall(state);}
            else if(name16 == IDENT::INVENTRUN)  {serial_print_shall("Is Ventilador, pin: "); serial_print_shall(pin16);serial_print_shall(" val: "); serial_println_shall(state);}
            else if(name16 == IDENT::TERMOSTATO) {serial_print_shall("Is Termostato, pin: "); serial_print_shall(pin16);serial_print_shall(" val: "); serial_println_shall(state);}  
            else if(name16 == IDENT::INQUEMOK)   {serial_print_shall("Is Alarma,     pin: "); serial_print_shall(pin16);serial_print_shall(" val: "); serial_println_shall(state);}
            else {serial_print_shall("*** DIGIREAD DESCONOCIDO **"); serial_println_shall(name16);}
#endif
            return state;
#else
            return false;
#endif
        }

        //----------------

        static void digital_Write(const uint8_t name, const uint8_t pin, const uint8_t state)
        {
#ifdef SHOW_IO
            uint16_t name16 = (uint16_t)name;
            uint16_t pin16 = (uint16_t)pin;
            uint16_t val16 = (uint16_t)state;
            if(name16 == IDENT::OUTVALVULA)    {serial_print_shall("     Valvula,      pin: "); serial_print_shall(pin16); serial_print_shall(" val: "); serial_println_shall(val16);}
            else if(name16 == IDENT::OUTROJA)  {serial_print_shall("     Baliza roja,  pin: "); serial_print_shall(pin16); serial_print_shall(" val: "); serial_println_shall(val16);}
            else if(name16 == IDENT::OUTVERDE) {serial_print_shall("     Baliza verde, pin: "); serial_print_shall(pin16); serial_print_shall(" val: "); serial_println_shall(val16);}  
            else if(name16 == IDENT::OUTVENT)  {serial_print_shall("     Ventilador,   pin: "); serial_print_shall(pin16); serial_print_shall(" val: "); serial_println_shall(val16);}
            else if(name16 == IDENT::OUTQUEM)  {serial_print_shall("     Quemador,     pin: "); serial_print_shall(pin16); serial_print_shall(" val: "); serial_println_shall(val16);}
            else {serial_print_shall("*** DIGIWRITE DESCONOCIDO **"); serial_println_shall(name16);}
#endif
#ifdef DEPLOY
            digitalWrite(pin, state);
#endif
        }

        //-----------------

        static void dac_Write(const uint8_t name, const uint8_t pin, const uint8_t value)
        {
#ifdef SHOW_IO
            uint16_t name16 = (uint16_t)name;
            uint16_t pin16 = (uint16_t)pin;
            uint16_t val16 = (uint16_t)value;                     
            if(name16 == IDENT::POWCOMBUST)     {serial_print_shall("     Pow Combust,  pin: "); serial_print_shall(pin16); serial_print_shall(" val: "); serial_println_shall(val16);}
            else if(name16 == IDENT::POWRESIST) {serial_print_shall("     Pow Resist,   pin: "); serial_print_shall(pin16); serial_print_shall(" val: "); serial_println_shall(val16);}
            else {serial_print_shall("*** DACWRITE DESCONOCIDO **"); serial_println_shall(name16);}
#endif
#ifdef DEPLOY
            return dacWrite(pin, value);
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

        //--------------------

        static inline unsigned long millisec() 
        {
#ifdef DEPLOY
            return millis();
#else   
            auto duration = std::chrono::system_clock::now().time_since_epoch();
            auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
            return millis;
#endif
        }

        //---------------------

        static inline unsigned long microsec() 
        {
#ifdef DEPLOY
            return micros();
#else   
            auto duration = std::chrono::system_clock::now().time_since_epoch();
            auto micros = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
            return micros;
#endif
        }

        //----------------------

        static inline void pinmode(uint8_t pin, uint8_t dir)
        {
#ifdef DEPLOY
            pinMode(pin, dir);
            serial_print_shall("pin: "); serial_print_shall((uint16_t)pin);
            serial_print_shall(" mode: "); serial_println_shall((uint16_t)dir);
#endif      
        }
};


#endif