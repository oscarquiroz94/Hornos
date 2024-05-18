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

        void interprete(Nextion& nx, Operativos& op)
        {

            strcpy(nx.com.comando, com.comando);

            if(com.comparar(com.comando, "POW,"))
            {
                
                char *listaValores = strtok(com.comando,",");

                listaValores = strtok(NULL,",");
                op.analogicos.potenciaQuem = (double)IEsp32::str2int(listaValores);
            }

            if (com.compararEqual(com.comando, "ISBURNER"))
            {
                op.confirmaciones.isQuemador = true;
            }

            if (com.compararEqual(com.comando, "ISNBURNER"))
            {
                op.confirmaciones.isQuemador = false;
            }

            if (com.compararEqual(com.comando, "ISFAN"))
            {
                op.confirmaciones.isVentilador = true;
            }

            if (com.compararEqual(com.comando, "ISNFAN"))
            {
                op.confirmaciones.isVentilador = false;
            }

            if (com.compararEqual(com.comando, "ISTERMO"))
            {
                op.confirmaciones.isTermostato = true;
            }

            if (com.compararEqual(com.comando, "ISNTERMO"))
            {
                op.confirmaciones.isTermostato = false;
            }

            if (com.compararEqual(com.comando, "ISALARM"))
            {
                op.confirmaciones.isAlarma = true;
            }

            if (com.compararEqual(com.comando, "ISNALARM"))
            {
                op.confirmaciones.isAlarma = false;
            }
            
            memset(com.comando, 0, com.sizecomand);
        }

        ~Debug(){}

};

#endif