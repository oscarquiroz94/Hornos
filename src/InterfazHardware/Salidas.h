#ifndef __OUTPUTS
#define __OUTPUTS

#include "IEsp32.h"
#include "InterfazOutputs.h"

class Salidas
{
    public:
        //Salidas() = default;
        Salidas(uint8_t tipo, uint8_t pinout)
        {
            tp = tipo;
            pin = pinout;
            IEsp32::serial_print("Salidas: instance created ");
            switch (tp)
            {
            case IDENT::OUTVALVULA :
                IEsp32::serial_print(" OUT valvula,");
                break;
            case IDENT::OUTROJA :
                IEsp32::serial_print(" OUT Baliza roja,");
                break;
            case IDENT::OUTVERDE :
                IEsp32::serial_print(" OUT Baliza verde,");
                break;
            case IDENT::OUTVENT :
                IEsp32::serial_print(" OUT Ventilador,");
                break;
            case IDENT::OUTQUEM :
                IEsp32::serial_print(" OUT Quemador,");
                break;
            default:
                break;
            }
            
            IEsp32::serial_print(" pin ");
            IEsp32::serial_println((uint16_t)pin);
        }

        void high() { interouts.digiwrite(tp, pin, true);}
        void low()  { interouts.digiwrite(tp, pin, false);}
        void set_mode(uint8_t pin, uint8_t mode) { IEsp32::pinmode(pin, mode); }

        ~Salidas()
        {
            IEsp32::serial_println("Salidas: instance deleted");
        }
    protected:
        uint8_t tp;
        uint8_t pin;
        InterfazOutputs interouts;
};

class SalidasAnalogica
{
    public:
        SalidasAnalogica(uint8_t name, uint8_t pinoutdac) 
        {
            type = name;
            pindac = pinoutdac;
            IEsp32::serial_print("Salidas Analogicas: instance created ");
            IEsp32::serial_println((uint16_t)type);
        }

        void set(uint8_t valor)
        {
            IEsp32::dac_Write(type, pindac, valor);
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