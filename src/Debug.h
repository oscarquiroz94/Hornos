#ifndef __DEBUG
#define __DEBUG

#include "Comunicacion.h"
#include "Operativos.h"

class Debug
{
    public:
        Debug(){}

        Comunicacion com;
        Operativos op_aux;

        void interprete()
        {
            IEsp32::serial_print("DEBUG: "); 
            IEsp32::serial_println(com.comando);

            if (com.compararEqual(com.comando, "ONQ"))
            {
                op_aux.eventos.onquemador = true;
            }

            if (com.compararEqual(com.comando, "OFFQ"))
            {
                op_aux.eventos.onquemador = false;
            }

            if (com.compararEqual(com.comando, "ONF"))
            {
                op_aux.eventos.onventilador = true;
            }

            if (com.compararEqual(com.comando, "OFFF"))
            {
                op_aux.eventos.onventilador = false;
            }

            if (com.compararEqual(com.comando, "ONV"))
            {
                op_aux.eventos.onvalvula = true;
            }

            if (com.compararEqual(com.comando, "OFFV"))
            {
                op_aux.eventos.onvalvula = false;
            }

            //---------------

            if (com.compararEqual(com.comando, "ISQ"))
            {
                op_aux.confirmaciones.isQuemador = true;
            }

            if (com.compararEqual(com.comando, "ISNQ"))
            {
                op_aux.confirmaciones.isQuemador = false;
            }

            if (com.compararEqual(com.comando, "ISV"))
            {
                op_aux.confirmaciones.isVentilador = true;
            }

            if (com.compararEqual(com.comando, "ISNV"))
            {
                op_aux.confirmaciones.isVentilador = false;
            }

            if (com.compararEqual(com.comando, "IST"))
            {
                op_aux.confirmaciones.isTermostato = true;
            }

            if (com.compararEqual(com.comando, "ISNT"))
            {
                op_aux.confirmaciones.isTermostato = false;
            }

            if (com.compararEqual(com.comando, "ISA"))
            {
                op_aux.confirmaciones.isAlarma = true;
            }

            if (com.compararEqual(com.comando, "ISNA"))
            {
                op_aux.confirmaciones.isAlarma = false;
            }
            
            memset(com.comando, 0, com.sizecomand);
        }

        Operativos& get_instance_op() {return op_aux;} 
        
        ~Debug(){}

};

#endif