#ifndef __OPERATIVOS
#define __OPERATIVOS

class Operativos
{
    public:
        Operativos(){}

        struct Eventos
        {
            bool onventilador = false;
            bool onquemador   = false;
        } eventos;

        struct Analogicos
        {
            double tempera = 0.0;
            double temperaAux = 0.0;
        } analogicos;

        struct Confirmaciones
        {
            bool isQuemador = false;
            bool isVentilador = false;
            bool isAlarma = false;
            bool isTermostato = false;
            bool isAdicional = false;
        } confirmaciones;
        
        

        struct Stack
        {
            bool ventilacionEnable = true;

        } stack;
        
        
        ~Operativos(){}
};



#endif