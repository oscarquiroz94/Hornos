#ifndef __MOTOR
#define __MOTOR

#include "Identity.h"
#include "Esp32.h"

class Motor
{
    public:
        Motor(short tp) :
            running(IDENT::INVENTRUN)
        {
            type = tp;
            Esp32::serial_print("Motor: instance created ");
            Esp32::serial_println(type);
        }

        void on(){}
        void off(){}
        bool isRunning(){return running.read();}

        ~Motor()
        {
            Esp32::serial_println("Motor: instance deleted");
        }

    private:
        short    type;
        Entradas running;
};



#endif