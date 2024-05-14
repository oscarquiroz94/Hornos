#include "Nextion.h"


void Nextion::send_stack(Operativos& op)
{
    int8_t index_last_key = first_digit(op.stack.lastkey) - 1;
    uint8_t sizearray = sizeof(op.analogicos.clave)/sizeof(uint16_t) - 1;
    if (index_last_key > sizearray - 1) index_last_key = -1;
    uint16_t nextkey = op.analogicos.clave[index_last_key + 1];

    com.send(2, "n0", first_digit(nextkey));
}

void Nextion::send(Operativos& op)
{
    com.send(0, "n0", (uint16_t)op.analogicos.tempera);
}

void Nextion::receive(Operativos& op)
{
    if (com.compararEqual(com.comando, "BURNER"))
    {
        op.eventos.onquemador = op.eventos.onquemador == true ? false : true;
    }

    if (com.compararEqual(com.comando, "FAN"))
    {
        op.eventos.onventilador = op.eventos.onventilador == true ? false : true;
    }

    if (com.compararEqual(com.comando, "VALVE"))
    {
        op.eventos.onvalvula = op.eventos.onvalvula == true ? false : true;
    }

    if (com.compararEqual(com.comando, "STOPRAMPA"))
    {
        op.eventos.onramp = false;
    }

    if (com.compararEqual(com.comando, "RUNTIMER"))
    {
        op.eventos.ontimer = op.eventos.ontimer == true ? false : true;
    }

    if(com.comparar(com.comando, "SETPOINT,"))
    {
        char *listaValores = strtok(com.comando,",");

        listaValores = strtok(NULL,",");
        op.analogicos.setpoint = IEsp32::str2int(listaValores);
    }

    if(com.comparar(com.comando, "TIMERAMP,"))
    {
        char *listaValores = strtok(com.comando,",");

        listaValores = strtok(NULL,",");
        op.analogicos.tiemporampa = IEsp32::str2int(listaValores);
    }

    if(com.comparar(com.comando, "TIMER,"))
    {
        char *listaValores = strtok(com.comando,",");

        listaValores = strtok(NULL,",");
        op.analogicos.tiempotimer = IEsp32::str2int(listaValores);
    }

    if(com.comparar(com.comando, "RAMPA,"))
    {
        //Setear con este evento para no esperar TIMERAMP
        op.analogicos.tiemporampa = 0;
        op.eventos.onramp = true;

        char *listaValores = strtok(com.comando,",");

        for(uint8_t i = 0; i < 4; i++)
        {
            listaValores = strtok(NULL,",");
            op.analogicos.arrayTemperaturas[i] = IEsp32::str2int(listaValores);
        }

        for(uint8_t i = 0; i < 4; i++)
        {
            listaValores = strtok(NULL,",");
            op.analogicos.arrayTiempos[i] = IEsp32::str2int(listaValores);
        }

        for(uint8_t i = 4; i < 8; i++)
        {
            listaValores = strtok(NULL,",");
            op.analogicos.arrayTemperaturas[i] = IEsp32::str2int(listaValores);
        }

        for(uint8_t i = 4; i < 8; i++)
        {
            listaValores = strtok(NULL,",");
            op.analogicos.arrayTiempos[i] = IEsp32::str2int(listaValores);
        }

    }

    if(com.comparar(com.comando, "CLAVE,"))
    {
        char *listaValores = strtok(com.comando,",");

        listaValores = strtok(NULL,",");
        uint16_t clave = IEsp32::str2int(listaValores);
        uint16_t index = first_digit(clave) - 1;
        
        if(op.analogicos.clave[index] == clave) 
        {
            com.send("page 0");
            op.stack.lastkey = clave;
            op.stack.save();
        }
        
    }

    memset(com.comando, 0, com.sizecomand);
}

void Nextion::reset()
{
    IEsp32::serial_println("Reseteando INextion... ");

    com.send("rest");
    IEsp32::retardo(200);
}

int Nextion::first_digit(int x) 
{
    while (x > 9) {
        x /= 10;
    }
    return x;
}