#ifndef __OUTPUTS
#define __OUTPUTS

#include "Esp32.h"

class Salidas
{
    public:
        Salidas() = default;
        Salidas(short tp)
        {
            type = tp;
            Esp32::serial_print("Salidas: instance created ");
            Esp32::serial_println(type);
        }

        ~Salidas()
        {
            Esp32::serial_println("Salidas: instance deleted");
        }
    protected:
        short type;
};

class SalidasAnalogica : public Salidas
{
    public:
        SalidasAnalogica(short tp) 
        {
            type = tp;
            Esp32::serial_print("Salidas Analogicas: instance created ");
            Esp32::serial_println(type);
        }

        void set(short valor)
        {
            
        }

        ~SalidasAnalogica()
        {
            Esp32::serial_println("Salidas Analogicas: instance deleted");
        }
};


#endif