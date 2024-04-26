#ifndef __BALIZA
#define __BALIZA

#include "Identity.h"
#include "Esp32.h"
#include "Salidas.h"

class Baliza
{
    public:
        Baliza() :
            balizaRoja(IDENT::OUTROJA),
            balizaVerde(IDENT::OUTVERDE)
        {
            Esp32::serial_println("Baliza: instance created");
        }
        void on(){}
        void off(){}

        ~Baliza()
        {
            Esp32::serial_println("Baliza: instance deleted");
        }
    private:
        Salidas balizaRoja;
        Salidas balizaVerde;
        
};



#endif