#ifndef __CONTROL
#define __CONTROL

#include "Esp32.h"

class Control
{
    public:
        Control()
        {
            Esp32::serial_println("Control: instance created");
        }

        //Valor deseado de temperatura
        void set_valor_deseado(double valor){}

        //Porcentaje de potencia quemador
        double regular(){return 0.0;}

        ~Control()
        {
            Esp32::serial_println("Control: instance deleted");
        }
};



#endif