#ifndef __SUPERVISION
#define __SUPERVISION

#include "Esp32.h"
#include "Horno.h"

class Supervision
{
    public:
        Supervision()
        {
            Esp32::serial_println("Supervision: instance created");
        }

        void verify_all(Horno& horno)
        {
            verify_ventilador(horno);
            verify_quemador(horno);
            verify_alarma_quemador(horno);
            verify_termostato(horno);
        }

        //ToDo: ver como implementar lamdas
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
            Operativos* op = horno.get_instance_op();
            Nextion* nx = horno.get_instance_nextion();

            if (op == nullptr) return;
            if (nx == nullptr) return;

            if (op->confirmaciones.isAlarma)
            {
                nx->send_alarma_state(true);
            }else
            {
                nx->send_alarma_state(false);
            }
        }

        void verify_termostato(Horno& horno)
        {
            Operativos* op = horno.get_instance_op();
            Nextion* nx = horno.get_instance_nextion();

            if (op == nullptr) return;
            if (nx == nullptr) return;

            if (op->confirmaciones.isTermostato)
            {
                nx->send_termostato_state(true);
            }else
            {
                nx->send_termostato_state(false);
            }
        }

        ~Supervision()
        {
            Esp32::serial_println("Supervision: instance deleted");
        }
};


#endif