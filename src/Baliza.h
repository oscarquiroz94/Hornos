#ifndef __BALIZA
#define __BALIZA

#include "Identity.h"
#include "IEsp32.h"
#include "Salidas.h"

class Baliza
{
    public:
        Baliza() :
            balizaRoja(IDENT::OUTROJA, PIN_BALIZAROJA),
            balizaVerde(IDENT::OUTVERDE, PIN_BALIZAVERDE)
        {
            IEsp32::serial_println("Baliza: instance created");
        }

        void on_ok()    
        {
            balizaVerde.high();
            balizaRoja.low();
        }
        void on_no_ok() 
        {
            balizaVerde.low();
            balizaRoja.high();
        }

        void set_modes()
        {
            balizaRoja.set_mode(PIN_BALIZAROJA, OUTPUT);
            balizaVerde.set_mode(PIN_BALIZAVERDE, OUTPUT);
        }

        ~Baliza()
        {
            IEsp32::serial_println("Baliza: instance deleted");
        }
    private:
        Salidas balizaRoja;
        Salidas balizaVerde;

        static constexpr uint8_t PIN_BALIZAROJA    = 23;
        static constexpr uint8_t PIN_BALIZAVERDE   = 22;
};  



#endif