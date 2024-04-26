#ifndef __QUEMADOR
#define __QUEMADOR

#include "Identity.h"
#include "Esp32.h"
#include "Operativos.h"
#include "Entradas.h"
#include "Salidas.h"

class Quemador
{
    public:
        Quemador() :
            running(IDENT::INQUEMRUN),
            alarma(IDENT::INQUEMOK) {}

        Quemador(short tp) :
            running(IDENT::INQUEMRUN),
            alarma(IDENT::INQUEMOK)
        {
            type = tp;
            Esp32::serial_print("Quemador: instance created ");
            Esp32::serial_println(type);
        }

        void on(){}
        void off(){}
        virtual void set_potencia(double valor) 
        {
            static SalidasAnalogica combustion(IDENT::POWCOMBUST);
        }
        bool is_running() {return running.read();}
        bool is_alarma()  {return alarma.read();}

        ~Quemador()
        {
            Esp32::serial_println("Quemador: instance deleted");
        }
    protected:
        short  type;

    private:
        Entradas running;
        Entradas alarma;
};

class QuemadorResistivo : public Quemador
{
    public:
        QuemadorResistivo(short tp)
        {
            type = tp;
            Esp32::serial_print("QuemadorResistivo: instance created ");
            Esp32::serial_println(type);
        }

        void set_potencia(double valor) override 
        {
            static SalidasAnalogica resistiva(IDENT::POWRESIST);
        }  

        ~QuemadorResistivo()
        {
            Esp32::serial_println("QuemadorResistivo: instance deleted");
        }

};
#endif