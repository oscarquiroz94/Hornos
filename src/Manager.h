#ifndef __MANAGER
#define __MANAGER

#include "Horno.h"

class Manager
{
    public:
        Manager(){}

        void run(Horno& horno)
        {
            accion_lectura_temperatura(horno);
            accion_lectura_entradas(horno);
            accion_ventilador(horno);
            accion_quemador(horno);
        }

        void accion_lectura_temperatura(Horno& horno)
        {
            Operativos* op = horno.get_instance_op();
            SensorAnalogico* sensTemp = horno.get_instance_sensTempera();
            SensorAnalogico* sensTempAux = horno.get_instance_sensTemperaAux();

            if (op == nullptr) return;
            if (sensTemp == nullptr) return;
            if (sensTempAux == nullptr) return;

            op->analogicos.tempera = sensTemp->read();
            op->analogicos.temperaAux = sensTempAux->read();
        }

        void accion_lectura_entradas(Horno& horno)
        {
            Operativos* op = horno.get_instance_op();
            Quemador* quemador = horno.get_instance_quemador();
            Motor* ventilador = horno.get_instance_motor();
            Entradas* termostato = horno.get_instance_termostato();

            if (op == nullptr) return;
            if (quemador == nullptr) return;
            if (termostato == nullptr) return;

            op->confirmaciones.isQuemador = quemador->is_running();
            op->confirmaciones.isAlarma = quemador->is_alarma();
            op->confirmaciones.isTermostato = termostato->read();

            // Si se desactiva ventilador aun se quieren leer las otras entradas
            if (ventilador == nullptr) return;
            op->confirmaciones.isVentilador = ventilador->isRunning();
        }

        void accion_ventilador(Horno& horno)
        {
            Motor* motor = horno.get_instance_motor();
            Operativos* op = horno.get_instance_op();

            if (motor == nullptr) return;
            if (op == nullptr) return;

            if (op->eventos.onventilador)
            {
                motor->on();
            }else
            {
                motor->off();
            }
        }

        void accion_quemador(Horno& horno)
        {
            Quemador* quemador = horno.get_instance_quemador();
            Operativos* op = horno.get_instance_op();

            if (quemador == nullptr) return;
            if (op == nullptr) return;

            if (op->eventos.onquemador)
            {
                quemador->on();
            }else
            {
                quemador->off();
            }
        }

        ~Manager(){}

};

#endif