#ifndef __QUEMADOR
#define __QUEMADOR

#include "Identity.h"
#include "IEsp32.h"
#include "Operativos.h"
#include "Entradas.h"
#include "Salidas.h"

class Quemador
{
    public:
        // Quemador() :
        //     running(IDENT::INQUEMRUN, PIN_QUEM_RUNNING),
        //     alarma(IDENT::INQUEMOK, PIN_QUEM_ALARMA),
        //     pinonoff(IDENT::OUTQUEM, PIN_QUEM_ONOFF) {}

        Quemador(uint8_t tp) :
            running(IDENT::INQUEMRUN, PIN_QUEM_RUNNING),
            alarma(IDENT::INQUEMOK, PIN_QUEM_ALARMA),
            pinonoff(IDENT::OUTQUEM, PIN_QUEM_ONOFF)
        {
            type = tp;
            IEsp32::serial_print("Quemador: instance created ");
            IEsp32::serial_println((uint16_t)type);
        }

        void on()  { pinonoff.high(); }  
        void off() { pinonoff.low(); }

        virtual void set_potencia(double potencia) 
        {
            static SalidasAnalogica combustion(IDENT::POWCOMBUST, PIN_QUEM_POW);
            
            if (potencia < 0.0){potencia = 0.0;}
            if (potencia > 100.0){potencia = 100.0;}

            double min_porcent = 0.0;
            double max_porcent = 100.0;

            uint8_t bvel = (uint8_t)map_double
                (potencia, 0, 100, min_porcent*(255/100.0), max_porcent*(255/100.0));
            
            combustion.set(bvel);
        }

        double map_double(double x, double in_min, double in_max, double out_min, double out_max)
        {
            if(in_max == in_min) return -1.0; 
            return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
        }

        void set_modes()
        {
            pinonoff.set_mode(PIN_QUEM_ONOFF, OUTPUT);
        }

        bool is_running() {return running.read();}
        bool is_alarma()  {return alarma.read();}

        ~Quemador()
        {
            IEsp32::serial_println("Quemador: instance deleted");
        }
    protected:
        uint8_t  type;

    private:
        Entradas running;
        Entradas alarma;
        Salidas  pinonoff;

        static constexpr uint8_t PIN_QUEM_RUNNING  = 27;
        static constexpr uint8_t PIN_QUEM_ALARMA   = 35;
        static constexpr uint8_t PIN_QUEM_POW      = 25;
        static constexpr uint8_t PIN_QUEM_ONOFF    = 13;
};

class QuemadorResistivo : public Quemador
{
    public:
        QuemadorResistivo(uint8_t tp) : Quemador(tp)
        {
            type = tp;
            IEsp32::serial_print("QuemadorResistivo: instance created ");
            IEsp32::serial_println((uint16_t)type);
        }

        void set_potencia(double valor) override 
        {
            static SalidasAnalogica resistiva(IDENT::POWRESIST, PIN_QUEM_POW);
        }  

        ~QuemadorResistivo()
        {
            IEsp32::serial_println("QuemadorResistivo: instance deleted");
        }

    private:
        static constexpr uint8_t PIN_QUEM_POW     = 26;

};
#endif