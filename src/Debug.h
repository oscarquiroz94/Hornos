#ifndef __DEBUG
#define __DEBUG

#include "Comunicacion.h"
#include "Operativos.h"
#include "Nextion.h"

class Debug
{
    public:
        Debug(){}

        static Comunicacion com;

        void interprete(Operativos& op);

        ~Debug(){}

};

#endif