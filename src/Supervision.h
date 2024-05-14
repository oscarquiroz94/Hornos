#ifndef __SUPERVISION
#define __SUPERVISION

#include "IEsp32.h"
#include "Horno.h"

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
        void verify_run(Horno& horno);
};


#endif