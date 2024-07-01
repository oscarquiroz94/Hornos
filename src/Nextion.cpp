#include "Nextion.h"

Comunicacion Nextion::com;

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

    if (op.eventos.onramp)
        com.send(0, "n1", (uint16_t)op.analogicos.setpoint);
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

        //Setear con este evento para no esperar TIMERNX
        op.analogicos.timernx = 0;
    }

    if(com.comparar(com.comando, "SETPOINT,"))
    {
        char *listaValores = strtok(com.comando,",");

        listaValores = strtok(NULL,",");
        op.analogicos.setpoint = IEsp32::str2int(listaValores);

        guardar();
    }

    if(com.comparar(com.comando, "TIMERNX,"))
    {
        char *listaValores = strtok(com.comando,",");

        listaValores = strtok(NULL,",");
        op.analogicos.timernx = IEsp32::str2int(listaValores);
    }

    if(com.comparar(com.comando, "TIMER,"))
    {
        char *listaValores = strtok(com.comando,",");

        listaValores = strtok(NULL,",");
        op.analogicos.tiempotimer = IEsp32::str2int(listaValores);

        guardar();
    }

    if(com.comparar(com.comando, "RAMPA,"))
    {
        if (!op.confirmaciones.isQuemador) 
        {
            com.send("page1.t2.txt=\"Burner not running\"");
            IEsp32::serial_println("Rampa: quemador no encendido");
            return;
        }

        //Setear con este evento para no esperar TIMERNX
        op.analogicos.timernx = 0;
        op.eventos.onramp = true;
    
#ifndef DEPLOY
        try
        {
#endif
            char *listaValores = strtok(com.comando,",");

            // RAMPA,160,140,120,100,0,10,20,30,160,140,120,100,0,10,20,30
            // arrayTemperaturas[8] = {100, 120, 140, 160, 100, 120, 140, 160};
            // arrayTiempos[8] = {0, 10, 20, 30, 0, 10, 20, 30};
            //---------------

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

            //----------------

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

#ifndef DEPLOY
        }
        catch(const std::exception& e)
        {
            std::cout << std::endl;
            std::cout << "*********** ERROR FATAL ************\n";
            std::cerr << e.what() << '\n';
            std::cout << "************************************\n";
            std::cout << std::endl;
        }
#endif

        

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

void Nextion::guardar()
{
    com.send("page0.b5.txt=\"Guardado\"");
    IEsp32::retardo(2000);
    com.send("page0.b5.txt=\"\"");
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