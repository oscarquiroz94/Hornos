#ifndef __INPUTS
#define __INPUTS

#include "IEsp32.h"
#include "max6675.h"
#include "InterfazInputs.h"

class Entradas
{
    public:
        Entradas(uint8_t name, uint8_t pin)
        {
            type = name;
            pin = pin;
            IEsp32::serial_print("Entradas: instance created ");
            IEsp32::serial_println((uint16_t)type);
        }

        bool read(){ return interinputs.digiread(type, pin);}

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
            temperatura(SCLK, CS, MISO)
        {
            type = tp;
            IEsp32::serial_print("Sensor Analogico: instance created ");
            IEsp32::serial_println((uint16_t)type);
        }

        double read(){ return temperatura.readCelsius();}

        ~SensorAnalogico()
        {
            IEsp32::serial_println("Sensor Analogico: instance deleted");
        }
    private:
        uint8_t type;
        MAX6675 temperatura;
};



#endif