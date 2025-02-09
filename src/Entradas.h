#ifndef __INPUTS
#define __INPUTS

#include "IEsp32.h"
#include "max6675.h"
#include "InterfazInputs.h"
#include "Temporizador.h"

class Entradas
{
    public:
        Entradas(uint8_t name, uint8_t pinout)
        {
            type = name;
            pin = pinout;
            IEsp32::serial_print("Entradas: instance created ");
            IEsp32::serial_println((uint16_t)type);
        }

        bool read(){ return interinputs.digiread(type, pin);}
        void set_mode(uint8_t pin, uint8_t mode) { IEsp32::pinmode(pin, mode); }


        ~Entradas()
        {
            IEsp32::serial_println("Entradas: instance deleted");
        }
    private:
        uint8_t type;
        uint8_t pin;
        InterfazInputs interinputs;
};

class SensorAnalogico
{
    public:
        SensorAnalogico(uint8_t tp, uint8_t SCLK, uint8_t CS, uint8_t MISO) :
            temperatura(SCLK, CS, MISO),
            tDelayRead(false, true)
        {
            type = tp;
            IEsp32::serial_print("Sensor Analogico: instance created ");
            IEsp32::serial_println((uint16_t)type);
        }

        double read()
        { 
            if (tDelayRead.tiempo(500))
                value = temperatura.readCelsius();

            return value;
        }

        ~SensorAnalogico()
        {
            IEsp32::serial_println("Sensor Analogico: instance deleted");
        }
    private:
        uint8_t type;
        MAX6675 temperatura;
        Temporizador tDelayRead;
        double value = 0.0;
};



#endif