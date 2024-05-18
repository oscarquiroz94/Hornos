#ifndef __INTERFAZINPUTS
#define __INTERFAZINPUTS

#include "Main.h"
#include "Identity.h"
#include "IEsp32.h"
#include "Debug.h"

extern Debug dbg;

class InterfazInputs
{
    public:
        InterfazInputs(){}

        bool digiread(const uint8_t name, const uint8_t pin)
        {
#ifdef DEPLOY
            return IEsp32::digital_Read(name, pin);
#else
            switch (name)
            {
            case IDENT::INQUEMRUN :
                return dbg.op_aux.confirmaciones.isQuemador;

            case IDENT::INVENTRUN :
                return dbg.op_aux.confirmaciones.isVentilador;

            case IDENT::TERMOSTATO :
                return dbg.op_aux.confirmaciones.isTermostato;

            case IDENT::INQUEMOK :
                return dbg.op_aux.confirmaciones.isAlarma;
            
            default:
                IEsp32::serial_print("*** Sensor interfaz input NO definido: ");
                IEsp32::serial_print((uint16_t)name);
                IEsp32::serial_println(" ***");
                return -1.0;
            }
#endif
        }

        ~InterfazInputs(){}
};



#endif