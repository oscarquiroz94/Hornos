#ifndef __OUTPUTS
#define __OUTPUTS

#include "IEsp32.h"
#include "InterfazOutputs.h"

class Salidas
{
    public:
        //Salidas() = default;
        Salidas(uint8_t tp, uint8_t pin)
        {
            type = tp;
            IEsp32::serial_print("Salidas: instance created ");
            IEsp32::serial_println((uint16_t)type);
        }

        void high() {interouts.digiwrite(type, pin, true);}
        void low()  {interouts.digiwrite(type, pin, true);}

        ~Salidas()
        {
            IEsp32::serial_println("Salidas: instance deleted");
        }
    protected:
        uint8_t type;
        uint8_t pin;
        InterfazOutputs interouts;
};

class SalidasAnalogica
{
    public:
        SalidasAnalogica(uint8_t name, uint8_t pindac) 
        {
            type = name;
            pindac = pindac;
            IEsp32::serial_print("Salidas Analogicas: instance created ");
            IEsp32::serial_println((uint16_t)type);
        }

        void set(uint8_t valor)
        {
            IEsp32::dac_Write(pindac, valor);
        }

        ~SalidasAnalogica()
        {
            IEsp32::serial_println("Salidas Analogicas: instance deleted");
        }
    private:
        uint8_t type;
        uint8_t pindac;
};


#endif