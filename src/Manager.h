#ifndef __MANAGER
#define __MANAGER

#include "IEsp32.h"
#include "Horno.h"
#include "EmuladorPlanta.h"

class Manager
{
    public:
        Manager() : emuladortempera(10.0, 0.2, 480.0)
        {
            IEsp32::serial_println("Manager: instance created");
        }

        void run(Horno& horno);

        ~Manager()
        {
            IEsp32::serial_println("Manager: instance deleted");
        }

    private:
        EmuladorPlanta emuladortempera;

        void accion_lectura_temperatura(Horno& horno);
        void accion_lectura_entradas(Horno& horno);
        void accion_ventilador(Horno& horno);
        void accion_quemador(Horno& horno);
        void accion_potencia_quemador(Horno& horno);
        void accion_control(Horno& horno);
        void accion_valvula(Horno& horno);
        void accion_baliza(Horno& horno);
        void accion_rampa(Horno& horno);
};

#endif