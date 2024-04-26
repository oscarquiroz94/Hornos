#ifndef __OPERATIVOS
#define __OPERATIVOS

#include "Esp32.h"
#include "Main.h"

#ifdef DEPLOY
    #include <EEPROM.h>
#endif

class Operativos
{
    public:
        Operativos()
        {
            Esp32::serial_println("Operativos: instance created");
        }

        struct Eventos
        {
            bool onventilador = false;
            bool onquemador   = false;
        } eventos;

        struct Analogicos
        {
            double tempera = 0.0;
            double temperaAux = 0.0;
            double potenciaQuem = 0.0;
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
            bool resistivoEnable = true;

            void save()
            {
            #ifdef DEPLOY
                int registro;

                registro = 0;
                EEPROM.put(registro, opuint8);

                registro += (int)sizeof(opuint8);
                EEPROM.put(registro, opuint16);

                registro += (int)sizeof(opuint16);
                EEPROM.put(registro, opuint32);

                registro += (int)sizeof(opuint32);
                EEPROM.put(registro, opbool);

                registro += (int)sizeof(opbool);
                EEPROM.put(registro, opdouble);

                registro += (int)sizeof(opdouble);
                EEPROM.put(registro, opchar);
            #endif
                //Atmega::serial_println(F("Stack: Updated"));

                //print();
            }
        } stack;

        ~Operativos()
        {
            Esp32::serial_println("Operativos: instance deleted");
        }
};



#endif