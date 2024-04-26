#ifndef __NEXTION
#define __NEXTION

#include "Esp32.h"
#include "Comunicacion.h"

class Nextion
{
    public:
        Nextion()
        {
            Esp32::serial_println("Nextion: instance created");
        }

        void send_motor_state(bool state)
        {
            com.send("page0.vis..state");
        }
        void send_quemador_state(bool state)
        {
            com.send("page0.vis..state");
        }
        void send_alarma_state(bool state)
        {
            com.send("page0.vis..state");
        }
        void send_termostato_state(bool state)
        {
            com.send("page0.vis..state");
        }

        ~Nextion()
        {
            Esp32::serial_println("Nextion: instance deleted");
        }

    private:
        Comunicacion com;
};


#endif