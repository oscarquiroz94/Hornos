#ifndef __NEXTION
#define __NEXTION

#include "IEsp32.h"
#include "Comunicacion.h"
#include "Operativos.h"

class Nextion
{
    public:
        Nextion()
        {
            IEsp32::serial_println("Nextion: instance created");
        }

        static Comunicacion com;
        
        void receive(Operativos& op);
        void send(Operativos& op);
        void send_stack(Operativos& op);
        void reset();

        void send_motor_state(bool state)
        {
            if (!state)
            {
                com.send("page0.b2.bco=44373");
                com.send("page0.b2.bco2=27501");
            }else
            {
                com.send("page0.b2.bco=1760");
                com.send("page0.b2.bco2=1315");
            }
        }

        void send_quemador_state(bool state)
        {
            if (!state)
            {
                com.send("page0.b1.bco=44373");
                com.send("page0.b1.bco2=27501");
            }else
            {
                com.send("page0.b1.bco=1760");
                com.send("page0.b1.bco2=1315");
            }
        }

        void send_valve_state(bool state)
        {
            if (!state)
            {
                com.send("page0.b3.bco=44373");
                com.send("page0.b3.bco2=27501");
            }else
            {
                com.send("page0.b3.bco=1760");
                com.send("page0.b3.bco2=1315");
            }
        }

        void send_run_state(bool state)
        {
            if (!state)
            {
                com.send("page0.b6.bco=44373");
                com.send("page0.b6.bco2=27501");
                
            }else
            {
                com.send("page0.b6.bco=1760");
                com.send("page0.b6.bco2=1315");
            }
        }

        void send_alarma_state(bool state)
        {
            
        }
        void send_termostato_state(bool state)
        {
            //com.send("page0.vis..state");
        }
        

        ~Nextion()
        {
            IEsp32::serial_println("Nextion: instance deleted");
        }

    private:
        int first_digit(int x);
};


#endif