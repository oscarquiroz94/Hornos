#ifndef __INPUTS
#define __INPUTS

#include "Esp32.h"

class Entradas
{
    public:
        Entradas(short tp)
        {
            type = tp;
            Esp32::serial_print("Entradas: instance created ");
            Esp32::serial_println(type);
        }

        bool read(){ return false;}

        ~Entradas()
        {
            Esp32::serial_println("Entradas: instance deleted");
        }
    private:
        short type;
};

class SensorAnalogico
{
    public:
        SensorAnalogico(short tp)
        {
            type = tp;
            Esp32::serial_print("Sensor Analogico: instance created ");
            Esp32::serial_println(type);
        }

        double read(){ return 0.0;}

        ~SensorAnalogico()
        {
            Esp32::serial_println("Sensor Analogico: instance deleted");
        }
    private:
        short type;
};



#endif