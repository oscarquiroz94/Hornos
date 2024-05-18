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
            IEsp32::digital_Write(name, pin, state);
        }

        ~InterfazOutputs(){}
};



#endif