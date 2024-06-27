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
        Operativos op_aux;

        void interprete(Nextion& nx, Operativos& op);

        ~Debug(){}

};

#endif