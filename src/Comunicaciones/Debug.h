#ifndef __DEBUG
#define __DEBUG

#include "Comunicacion.h"
#include "../Control/Operativos.h"
#include "../InterfazVisual/Nextion.h"

class Debug
{
    public:
        Debug(){}

        static Comunicacion com;

        void interprete(Operativos& op);

        ~Debug(){}

};

#endif