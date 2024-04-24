#ifndef __SUPERVISION
#define __SUPERVISION

#include "Horno.h"

class Supervision
{
    public:
        Supervision(){}

        void verify_all(Horno& horno)
        {
            verify_ventilador(horno);
            verify_quemador(horno);
            verify_alarma_quemador(horno);
            verify_termostato(horno);
        }

        void verify_ventilador(Horno& horno)
        {
            Motor* motor = horno.get_instance_motor();
            Nextion* nx = horno.get_instance_nextion();

            if (motor == nullptr) return;
            if (nx == nullptr) return;

            if (motor->isRunning())
            {
                nx->send_motor_state(true);
            }else
            {
                nx->send_motor_state(false);
            }
        }

        void verify_quemador(Horno& horno)
        {
            Operativos* op = horno.get_instance_op();
            Nextion* nx = horno.get_instance_nextion();

            if (op == nullptr) return;
            if (nx == nullptr) return;

            if (op->confirmaciones.isQuemador)
            {
                nx->send_quemador_state(true);
            }else
            {
                nx->send_quemador_state(false);
            }
        }

        void verify_alarma_quemador(Horno& horno)
        {

        }

        void verify_termostato(Horno& horno)
        {

        }

        ~Supervision(){}
};


#endif