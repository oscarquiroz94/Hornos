#ifndef __HORNO
#define __HORNO

#include "Identity.h"
#include "Esp32.h"
#include "Quemador.h"
#include "Motor.h"
#include "Control.h"
#include "Operativos.h"
#include "Nextion.h"
#include "Entradas.h"
#include "Salidas.h"
#include "Baliza.h"

class Horno
{
    public:
        Horno() :
            termostato(IDENT::TERMOSTATO),
            valvula(IDENT::OUTVALVULA),
            sensTempera(IDENT::SENSTEMPERA),
            sensTemperaAux(IDENT::SENSTEMPAUX)
        {
            Esp32::serial_println("Horno: instance created");
        }

        Operativos* get_instance_op()         {return &op;}
        
        Nextion*    get_instance_nextion()    {return &nx;}
        Entradas*   get_instance_termostato() {return &termostato;}
        Salidas*    get_instance_valvula()    {return &valvula;}
        Baliza*     get_instance_baliza()     {return &baliza;}
        Control*    get_instace_pid()         {return &pid;}
        SensorAnalogico* get_instance_sensTempera()    {return &sensTempera;} 
        SensorAnalogico* get_instance_sensTemperaAux() {return &sensTemperaAux;} 

        Motor* get_instance_motor()
        {
            if (op.stack.ventilacionEnable)
            {
                static Motor ventilador(IDENT::VENTILADOR);
                return &ventilador;
            }else
            {
                return nullptr;
            }
        }

        Quemador* get_instance_quemador()   
        {
            if (op.stack.resistivoEnable)
            {
                static QuemadorResistivo quemador(IDENT::QUEMRESIST);
                return &quemador;
            }else
            {
                static Quemador quemador(IDENT::QUEMADOR);
                return &quemador;
            }
            
        }

        ~Horno()
        {
            Esp32::serial_println("Horno: instance deleted");
        }
    
    private:
        Operativos op;
        
        Control    pid;
        Nextion    nx;
        Entradas   termostato;  
        Salidas    valvula;
        Baliza     baliza;
        SensorAnalogico  sensTempera;
        SensorAnalogico  sensTemperaAux;

};


#endif