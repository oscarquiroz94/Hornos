#ifndef __HORNO
#define __HORNO

#include "Quemador.h"
#include "Motor.h"
#include "Control.h"
#include "Operativos.h"
#include "Nextion.h"
#include "Entradas.h"

class Horno
{
    public:
        Horno(){}

        Operativos* get_instance_op()         {return &op;}
        Quemador*   get_instance_quemador()   {return &quemador;}
        Nextion*    get_instance_nextion()    {return &nx;}
        Entradas*   get_instance_termostato() {return &termostato;}
        SensorAnalogico* get_instance_sensTempera()    {return &sensTempera;} 
        SensorAnalogico* get_instance_sensTemperaAux() {return &sensTemperaAux;} 

        Motor* get_instance_motor()
        {
            if (!op.stack.ventilacionEnable) return nullptr;

            if (ventilador != nullptr) return ventilador;
            else ventilador = new Motor();
        }

        ~Horno()
        {
            if (ventilador != nullptr) delete ventilador;
        }
    
    private:
        Operativos op;
        Quemador   quemador;
        Control    pid;
        Nextion    nx;
        Entradas   termostato;  
        SensorAnalogico  sensTempera;
        SensorAnalogico  sensTemperaAux;

        Motor*     ventilador;

};


#endif