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

        void interprete(Nextion& nx, Operativos& op)
        {
            //Copiar comandos de consola en ordenes a Nextion
            strcpy(nx.com.comando, com.comando);
            
            if(com.comparar(com.comando, "POW,"))
            {
                char *listaValores = strtok(com.comando,",");

                listaValores = strtok(NULL,",");
                op.analogicos.potenciaQuem = (double)IEsp32::str2int(listaValores);
            }

            if (com.compararEqual(com.comando, "ISBURNER"))
            {
                op_aux.confirmaciones.isQuemador = true;
            }

            if (com.compararEqual(com.comando, "ISNBURNER"))
            {
                op_aux.confirmaciones.isQuemador = false;
            }

            if (com.compararEqual(com.comando, "ISFAN"))
            {
                op_aux.confirmaciones.isVentilador = true;
            }

            if (com.compararEqual(com.comando, "ISNFAN"))
            {
                op_aux.confirmaciones.isVentilador = false;
            }

            if (com.compararEqual(com.comando, "ISTERMO"))
            {
                op_aux.confirmaciones.isTermostato = true;
            }

            if (com.compararEqual(com.comando, "ISNTERMO"))
            {
                op_aux.confirmaciones.isTermostato = false;
            }

            if (com.compararEqual(com.comando, "ISALARM"))
            {
                op_aux.confirmaciones.isAlarma = true;
            }

            if (com.compararEqual(com.comando, "ISNALARM"))
            {
                op_aux.confirmaciones.isAlarma = false;
            }
            
            memset(com.comando, 0, com.sizecomand);
        }

        ~Debug(){}

};

#endif