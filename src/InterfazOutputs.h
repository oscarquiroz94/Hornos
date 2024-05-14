#ifndef __INTERFAZOUTPUTS
#define __INTERFAZOUTPUTS

#include "Main.h"
#include "Identity.h"
#include "IEsp32.h"
#include "Debug.h"

extern Debug dbg;

class InterfazOutputs
{
    public:
        InterfazOutputs(){}

        void digiwrite(const uint8_t name, const uint8_t pin, const uint8_t state)
        {
#ifndef OUTFROM_CONSOLE
            IEsp32::digital_Write(name, pin, state);
#else
            switch (name)
            {
            case IDENT::OUTVALVULA :
                IEsp32::digital_Write(name, pin, dbg.op_aux.eventos.onvalvula);
                break;

            case IDENT::OUTVENT :
                IEsp32::digital_Write(name, pin, dbg.op_aux.eventos.onventilador);
                break;

            case IDENT::OUTQUEM :
                IEsp32::digital_Write(name, pin, dbg.op_aux.eventos.onquemador);
                break;
            
            default:
                IEsp32::serial_print("*** Sensor interfaz output NO definido: ");
                IEsp32::serial_print((uint16_t)name);
                IEsp32::serial_println(" ***");
                break;
            }
#endif
        }

        ~InterfazOutputs(){}
};



#endif