#include "Debug.h"

Comunicacion Debug::com;

void Debug::interprete(Operativos& op)
{
    if(com.comparar(com.comando, "POW,"))
    {
        char *listaValores = strtok(com.comando,",");

        listaValores = strtok(NULL,",");
        op.analogicos.potenciaQuem = (double)IEsp32::str2int(listaValores);
    }

    if(com.comparar(com.comando, "TEMP,"))
    {
        char *listaValores = strtok(com.comando,",");

        listaValores = strtok(NULL,",");
        op.analogicos.tempera = (double)IEsp32::str2int(listaValores);
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