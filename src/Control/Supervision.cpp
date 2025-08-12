#include "Supervision.h"

void Supervision::verify_all(Horno& horno)
{
    verify_ventilador(horno);
    verify_quemador(horno);
    verify_alarma_quemador(horno);
    verify_termostato(horno);
    verify_valve(horno);
    verify_timer_started(horno);
    verify_ramp_started(horno);
}

void Supervision::verify_ventilador(Horno& horno)
{
    Operativos* op = &horno.get_instance_op();
    Motor* motor = horno.get_instance_motor();
    Nextion* nx = &horno.get_instance_nextion();

    if (op == nullptr) return;
    if (motor == nullptr) return;
    if (nx == nullptr) return;

    if (op->confirmaciones.isVentilador)
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

void Supervision::verify_timer_started(Horno& horno)
{
    Operativos* op = &horno.get_instance_op();
    Nextion* nx = &horno.get_instance_nextion();

    if (op == nullptr) return;
    if (nx == nullptr) return;

    IEsp32::serial_println("supervision timer");

    //---------------

    if (!op->confirmaciones.isQuemador) op->eventos.ontimer = false;

    uint16_t tiemporunning = op->analogicos.timernx - op->analogicos.lasttimernx;

    if (op->eventos.ontimer)
    {
#ifdef DEPLOY
        String cadena = "page0.b5.txt=\"Running for: \"" + String(tiemporunning); + "\"min\"";
#else
        std::string cadena = "page0.b5.txt=\"Running for: " + std::to_string(tiemporunning) + " min\"";
        nx->com.send(&cadena[0]);
#endif
        nx->send_timer_state(true);
    }else
    {
        nx->send_timer_state(false);
        nx->com.send("page0.b5.txt=\"\"");
    }
}

void Supervision::verify_ramp_started(Horno& horno)
{
    Operativos* op = &horno.get_instance_op();
    Nextion* nx = &horno.get_instance_nextion();

    if (op == nullptr) return;
    if (nx == nullptr) return;

    IEsp32::serial_println("supervision ramp");

    if (op->confirmaciones.isQuemador && op->eventos.onramp)
    {
#ifdef DEPLOY
        String cadena = "page1.t2.txt=\"Running for: \"" + String(op->analogicos.timernx); + "\"min\"";
#else
        std::string cadena = "page1.t2.txt=\"Running for: " + std::to_string(op->analogicos.timernx) + " min\"";
        nx->com.send(&cadena[0]);
#endif
    }else if (op->confirmaciones.isQuemador && !op->eventos.onramp)
    {
        nx->com.send("page1.t2.txt=\"\"");
    }
}