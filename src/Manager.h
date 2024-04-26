#ifndef __MANAGER
#define __MANAGER

#include "Esp32.h"
#include "Horno.h"

class Manager
{
    public:
        Manager()
        {
            Esp32::serial_println("Manager: instance created");
        }

        void run(Horno& horno)
        {
            accion_lectura_temperatura(horno);
            accion_lectura_entradas(horno);
            accion_ventilador(horno);
            accion_quemador(horno);
            accion_control(horno);
            accion_potencia_quemador(horno);
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

            Esp32::serial_println("accion lectura temperatura");
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

            Esp32::serial_println("accion lectura entradas");
        }

        void accion_ventilador(Horno& horno)
        {
            Motor* ventilador = horno.get_instance_motor();
            Operativos* op = horno.get_instance_op();

            if (ventilador == nullptr) return;
            if (op == nullptr) return;

            if (op->eventos.onventilador)
            {
                ventilador->on();
            }else
            {
                ventilador->off();
            }

            Esp32::serial_println("accion ventilador");
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

            Esp32::serial_println("accion quemador");
        }

        void accion_potencia_quemador(Horno& horno)
        {
            Quemador* quemador = horno.get_instance_quemador();
            Operativos* op = horno.get_instance_op();

            if (quemador == nullptr) return;
            if (op == nullptr) return;

            quemador->set_potencia(op->analogicos.potenciaQuem); //Porcentaje

            Esp32::serial_println("accion potencia quemador");
        }

        void accion_control(Horno& horno)
        {
            Operativos* op = horno.get_instance_op();
            Control* pid = horno.get_instace_pid();

            if (op == nullptr) return;
            if (pid == nullptr) return;

            pid->set_valor_deseado(10.0);
            op->analogicos.potenciaQuem = pid->regular();

            Esp32::serial_println("accion control");
        }

        void accion_valvula(Horno& horno)
        {
            //Logica para accionar valvula
            Salidas* valvula = horno.get_instance_valvula();

            Esp32::serial_println("accion valvula");
        }

        void accion_baliza(Horno& horno)
        {
            //Logica para accionar baliza
            Baliza* baliza = horno.get_instance_baliza();

            Esp32::serial_println("accion baliza");
        }

        ~Manager()
        {
            Esp32::serial_println("Manager: instance deleted");
        }

};

#endif