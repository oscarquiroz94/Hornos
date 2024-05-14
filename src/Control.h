#ifndef __CONTROL
#define __CONTROL

#include "IEsp32.h"

class Control
{
    public:
        Control()
        {
            IEsp32::serial_println("Control: instance created");
        }

        void set_temperatura_deseada(double valor){}

        //Porcentaje de potencia quemador
        double regular(){return 0.0;}

        ~Control()
        {
            IEsp32::serial_println("Control: instance deleted");
        }
};



#endif