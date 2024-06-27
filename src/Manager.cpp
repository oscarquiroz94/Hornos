#include "Manager.h"

void Manager::run(Horno& horno)
{
    horno.get_instance_nextion().receive(horno.get_instance_op());
    horno.get_instance_nextion().send(horno.get_instance_op());
    horno.get_instance_op().print();

    accion_lectura_temperatura(horno);
    accion_lectura_entradas(horno);
    accion_ventilador(horno);
    accion_quemador(horno);
    accion_valvula(horno);
    accion_baliza(horno);

    if (horno.get_instance_op().eventos.onramp) 
    {
        accion_rampa(horno);
    }else
    {
        accion_control(horno);
    }
    
    accion_potencia_quemador(horno);
    
}

void Manager::accion_lectura_temperatura(Horno& horno)
{
    IEsp32::serial_println("accion lectura temperatura");

    Operativos* op = &horno.get_instance_op();
    SensorAnalogico* sensTemp = &horno.get_instance_sensTempera();
    SensorAnalogico* sensTempAux = &horno.get_instance_sensTemperaAux();

    if (op == nullptr) return;
    if (sensTemp == nullptr) return;
    if (sensTempAux == nullptr) return;

    op->analogicos.tempera = sensTemp->read();
    op->analogicos.temperaAux = sensTempAux->read();
}

void Manager::accion_lectura_entradas(Horno& horno)
{
    IEsp32::serial_println("accion lectura entradas");

    Operativos* op = &horno.get_instance_op();
    Quemador* quemador = horno.get_instance_quemador();
    Motor* ventilador = horno.get_instance_motor();
    Entradas* termostato = &horno.get_instance_termostato();

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

void Manager::accion_ventilador(Horno& horno)
{
    IEsp32::serial_println("accion ventilador");

    Motor* ventilador = horno.get_instance_motor();
    Operativos* op = &horno.get_instance_op();

    if (ventilador == nullptr) return;
    if (op == nullptr) return;

    if (op->eventos.onventilador)
    {
        ventilador->on();
    }else
    {
        ventilador->off();
    }
}

void Manager::accion_quemador(Horno& horno)
{
    IEsp32::serial_println("accion quemador");

    Quemador* quemador = horno.get_instance_quemador();
    Operativos* op = &horno.get_instance_op();

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

void Manager::accion_potencia_quemador(Horno& horno)
{
    IEsp32::serial_println("accion potencia quemador");

    Quemador* quemador = horno.get_instance_quemador();
    Operativos* op = &horno.get_instance_op();

    if (quemador == nullptr) return;
    if (op == nullptr) return;

    quemador->set_potencia(op->analogicos.potenciaQuem); //Porcentaje
}

void Manager::accion_control(Horno& horno)
{
    IEsp32::serial_println("accion control");

    Operativos* op = &horno.get_instance_op();
    Control* pid = &horno.get_instace_pid();

    if (op == nullptr) return;
    if (pid == nullptr) return;
    if (!op->confirmaciones.isQuemador) return;

    pid->set_temperatura_deseada(op->analogicos.setpoint);

    //! Deshabilitado para testing Etapa 3
    //op->analogicos.potenciaQuem = pid->regular();  
}

void Manager::accion_rampa(Horno& horno)
{
    IEsp32::serial_println("accion rampa");

    Operativos* op = &horno.get_instance_op();
    Control* pid = &horno.get_instace_pid();

    if (op == nullptr) return;
    if (pid == nullptr) return;
    if (!op->confirmaciones.isQuemador) return;

    for (uint8_t i = 0; i < 8; i++)
    {
        if (op->analogicos.tiemporampa == op->analogicos.arrayTiempos[i])
        {
            pid->set_temperatura_deseada((double)op->analogicos.arrayTemperaturas[i]);
        }
    }

    //! Deshabilitado para testing Etapa 3
    //op->analogicos.potenciaQuem = pid->regular(); 
}

void Manager::accion_valvula(Horno& horno)
{
    IEsp32::serial_println("accion valvula");

    Operativos* op = &horno.get_instance_op();
    Salidas* valvula = &horno.get_instance_valvula();

    if (valvula == nullptr) return;
    if (op == nullptr) return;

    if (op->eventos.onvalvula)
    {
        valvula->high();
    }else
    {
        valvula->low();
    }
}

void Manager::accion_baliza(Horno& horno)
{
    IEsp32::serial_println("accion baliza");
    
    //Logica para accionar baliza
    //Baliza* baliza = &horno.get_instance_baliza();
}

