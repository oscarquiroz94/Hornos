#ifndef __NEXTION
#define __NEXTION

#include "Comunicacion.h"

class Nextion
{
    public:
        Nextion(){}
        void send_motor_state(bool state)
        {
            com.send("page0.vis..state");
        }
        void send_quemador_state(bool state)
        {
            com.send("page0.vis..state");
        }
        ~Nextion(){}

    private:
        Comunicacion com;
};


#endif