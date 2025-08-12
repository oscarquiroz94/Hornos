#ifndef __SUPERVISION
#define __SUPERVISION

#include "../InterfazHardware/IEsp32.h"
#include "../InterfazHardware/Horno.h"

class Supervision
{
    public:
        Supervision()
        {
            IEsp32::serial_println("Supervision: instance created");
        }

        void verify_all(Horno& horno);

        ~Supervision()
        {
            IEsp32::serial_println("Supervision: instance deleted");
        }

    private:
        void verify_ventilador(Horno& horno);
        void verify_quemador(Horno& horno);
        void verify_alarma_quemador(Horno& horno);
        void verify_termostato(Horno& horno);
        void verify_valve(Horno& horno);
        void verify_timer_started(Horno& horno);
        void verify_ramp_started(Horno& horno);
};


#endif