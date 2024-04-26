#ifndef __COMUNICACION
#define __COMUNICACION

#include "Esp32.h"

class Comunicacion
{
    public:
        Comunicacion()
        {
            Esp32::serial_println("Comunicacion: instance created");
        }

        void send(const char* comando)
        {
            //Serial.print(comando);
        }

        ~Comunicacion()
        {
            Esp32::serial_println("Comunicacion: instance deleted");
        }
};



#endif