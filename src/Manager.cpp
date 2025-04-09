

#include "Manager.h"

void Manager::run(Horno& horno)
{
    Operativos* op = &horno.get_instance_op();

    horno.get_instance_nextion().receive
        (*op, horno.get_instance_stack());

    horno.get_instance_nextion().send
        (*op, horno.get_instance_stack());

    op->print();

    accion_lectura_temperatura(horno);
    accion_lectura_entradas(horno);
    accion_ventilador(horno);
    accion_quemador(horno);
    accion_valvula(horno);
    accion_baliza(horno);

    accion_control(horno);
    accion_rampa(horno);

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

#ifdef DEPLOY
    op->analogicos.tempera = sensTemp->read();
    op->analogicos.temperaAux = sensTempAux->read();
#else
    op->analogicos.tempera = emuladortempera.emular(op->analogicos.potenciaQuem);
    op->analogicos.temperaAux = sensTempAux->read();
#endif

    // //! Para simular incremento temperatura cuando valvula esta ON
    // if (!op->confirmaciones.isQuemador || !horno.get_instance_op().eventos.ontimer) return;
    // if (op->eventos.onvalvula) op->analogicos.tempera += 0.5;
    // else op->analogicos.tempera -= 0.5;
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


    //Quemador confirma encendido
    op->confirmaciones.isQuemador = quemador->is_running();

    //Quemador entra en falla
    op->confirmaciones.isAlarma = quemador->is_alarma();

    //Termoswitche se activa por sobretemperatura
    op->confirmaciones.isTermostato = termostato->read();


    // Si se desactiva ventilador aun se quieren leer las otras entradas
    if (ventilador == nullptr) return;
    //Ventilador confirma encendido
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

    if (!op->confirmaciones.isVentilador)
        op->eventos.onquemador = false;

    if (op->eventos.onquemador)
    {
        quemador->on();
    }else
    {
        quemador->off();
    }

    if (op->confirmaciones.isQuemador)
    {
        op->eventos.onvalvula = true;
    }else
    {
        op->eventos.onvalvula = false;
        op->analogicos.potenciaQuem = 0.0;
    }
}

void Manager::accion_control(Horno& horno)
{
    Operativos* op = &horno.get_instance_op();

    ControlOnOffpwm* accion = (ControlOnOffpwm*)horno.get_instace_controlador();

    if (op == nullptr) return;
    if (accion == nullptr) return;

    //----------------

    if (op->eventos.onramp) return; 

    if (!op->confirmaciones.isQuemador) return;
    if (!op->confirmaciones.isVentilador) return;

    if ((op->analogicos.timernx - op->analogicos.lasttimernx >= op->analogicos.tiempotimer)
        & op->eventos.ontimer)
    {
        op->eventos.ontimer = false;
        op->eventos.onquemador = false;
    }

    accion->set_temperatura_deseada(op->analogicos.setpoint);
    op->analogicos.potenciaQuem = accion->regular(*op);  

    if (accion->isInsideUmbral(*op) && !op->eventos.ontimer)
    {
        op->eventos.ontimer = true;
        op->analogicos.lasttimernx = op->analogicos.timernx;
    }
}

void Manager::accion_rampa(Horno& horno)
{
    Operativos* op = &horno.get_instance_op();
    ControlOnOffpwm* accion = (ControlOnOffpwm*)horno.get_instace_controlador();
    // ControlPid* pid = (ControlPid*)horno.get_instace_controlador();
    // ControlOnOff* c_onoff = (ControlOnOff*)horno.get_instace_controlador();

    if (op == nullptr) return;
    if (accion == nullptr) return;

    //------------------
    
    if (!op->eventos.onramp) return;

    if (!op->confirmaciones.isQuemador) 
    {
        op->eventos.onventilador = true;
        op->eventos.onquemador = true;
    }

    IEsp32::serial_println("accion rampa");

    for (uint8_t i = 0; i < 8; i++)
    {
        if (op->analogicos.timernx == op->analogicos.arrayTiempos[i])
        {
            op->analogicos.setpoint = (double)op->analogicos.arrayTemperaturas[i];
            accion->set_temperatura_deseada(op->analogicos.setpoint);
        }
    }
    
    op->analogicos.potenciaQuem = accion->regular(*op); 
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

void Manager::accion_valvula(Horno& horno)
{
    IEsp32::serial_println("accion valvula");

    Operativos* op = &horno.get_instance_op();
    Salidas* valvula = &horno.get_instance_valvula();

    if (valvula == nullptr) return;
    if (op == nullptr) return;

    if (op->eventos.onvalvula && op->confirmaciones.isQuemador)
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

