#include "Supervision.h"

void Supervision::verify_all(Horno& horno)
{
    verify_ventilador(horno);
    verify_quemador(horno);
    verify_alarma_quemador(horno);
    verify_termostato(horno);
    verify_valve(horno);
    verify_run(horno);
}

void Supervision::verify_ventilador(Horno& horno)
{
    Motor* motor = horno.get_instance_motor();
    Nextion* nx = &horno.get_instance_nextion();

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

void Supervision::verify_quemador(Horno& horno)
{
    Operativos* op = &horno.get_instance_op();
    Nextion* nx = &horno.get_instance_nextion();

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

void Supervision::verify_alarma_quemador(Horno& horno)
{
    Operativos* op = &horno.get_instance_op();
    Nextion* nx = &horno.get_instance_nextion();

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

void Supervision::verify_termostato(Horno& horno)
{
    Operativos* op = &horno.get_instance_op();
    Nextion* nx = &horno.get_instance_nextion();

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

void Supervision::verify_valve(Horno& horno)
{
    Operativos* op = &horno.get_instance_op();
    Nextion* nx = &horno.get_instance_nextion();

    if (op == nullptr) return;
    if (nx == nullptr) return;

    if (op->eventos.onvalvula)
    {
        nx->send_valve_state(true);
    }else
    {
        nx->send_valve_state(false);
    }
}

void Supervision::verify_run(Horno& horno)
{
    Operativos* op = &horno.get_instance_op();
    Nextion* nx = &horno.get_instance_nextion();

    if (op == nullptr) return;
    if (nx == nullptr) return;

    if (op->eventos.ontimer)
    {
        nx->send_run_state(true);
    }else
    {
        nx->send_run_state(false);
    }
}