#ifndef __OPERATIVOS
#define __OPERATIVOS

#include "IEsp32.h"
#include "Main.h"

#ifdef DEPLOY
    #include <EEPROM.h>
#endif

class Operativos
{
    public:
        Operativos()
        {
            IEsp32::serial_println("Operativos: instance created");
        }

        struct Eventos
        {
            bool onventilador = false;
            bool onquemador   = false;
            bool onvalvula    = false;
            bool onramp   = false;
            bool ontimer  = false;
        } eventos;

        struct Analogicos
        {
            double tempera = 0.0; 
            double temperaAux = 0.0;
            double potenciaQuem = 0.0;
            uint16_t setpoint = 100;
            uint16_t timernx = 0;
            uint32_t tiempotimer = 5;
            uint16_t arrayTemperaturas[8] = {100, 120, 140, 160, 100, 120, 140, 160};
            uint16_t arrayTiempos[8] = {0, 10, 20, 30, 0, 10, 20, 30};
            uint16_t clave[9] = {1223, 259, 36854, 43, 5078, 698, 76, 8671, 920};

        } analogicos;

        struct Confirmaciones
        {
            bool isQuemador = false;
            bool isVentilador = false;
            bool isAlarma = false;
            bool isTermostato = false;
            bool isAdicional = false;
        } confirmaciones;
        
        void print()
        {
            IEsp32::serial_print("Eventos onventilador: "); IEsp32::serial_println(eventos.onventilador);
            IEsp32::serial_print("Eventos onquemador: "); IEsp32::serial_println(eventos.onquemador);
            IEsp32::serial_print("Eventos onvalvula: "); IEsp32::serial_println(eventos.onvalvula);
            IEsp32::serial_print("Eventos onrampa: "); IEsp32::serial_println(eventos.onramp);
            IEsp32::serial_print("Eventos ontimer: "); IEsp32::serial_println(eventos.ontimer);
            IEsp32::serial_print("Analogi setpoint: "); IEsp32::serial_println(analogicos.setpoint);
            IEsp32::serial_print("Analogi tempera: "); IEsp32::serial_println(analogicos.tempera);
            IEsp32::serial_print("Analogi temperaAux: "); IEsp32::serial_println(analogicos.temperaAux);
            IEsp32::serial_print("Analogi potenciaQuem: "); IEsp32::serial_println(analogicos.potenciaQuem);
            IEsp32::serial_print("Analogi timernx: "); IEsp32::serial_println(analogicos.timernx);
            IEsp32::serial_print("Analogi timetimer: "); IEsp32::serial_println(analogicos.tiempotimer);
            IEsp32::serial_print("Confirm isQuemador: "); IEsp32::serial_println(confirmaciones.isQuemador);
            IEsp32::serial_print("Confirm isVentilador: "); IEsp32::serial_println(confirmaciones.isVentilador);
            IEsp32::serial_print("Confirm isAlarma: "); IEsp32::serial_println(confirmaciones.isAlarma);
            IEsp32::serial_print("Confirm isTermostato: "); IEsp32::serial_println(confirmaciones.isTermostato);
            IEsp32::serial_print("Confirm isAdicional: "); IEsp32::serial_println(confirmaciones.isAdicional);
            IEsp32::serial_print("Analogi arrayTemperatura: ");
            for(uint8_t i = 0; i < 8; i++)
            {
                IEsp32::serial_print(analogicos.arrayTemperaturas[i]);
                IEsp32::serial_print(", ");
            }
            IEsp32::serial_println("");
            IEsp32::serial_print("Analogi arrayTemperatura: ");
            for(uint8_t i = 0; i < 8; i++)
            {
                IEsp32::serial_print(analogicos.arrayTiempos[i]);
                IEsp32::serial_print(", ");
            }
            IEsp32::serial_println("");
        }

        ~Operativos()
        {
            IEsp32::serial_println("Operativos: instance deleted");
        }
};    


class Stack
{
    public:
        bool ventilacionEnable = true;
        bool resistivoEnable = false;
        bool controlOnOff = true;
        bool masterkeydone = false;
        uint16_t lastkey = 920;
        uint32_t masterkey = 5980510;


        void save()
        {
#ifdef DEPLOY
            int registro;
            registro = 0;

            EEPROM.writeBool(registro, ventilacionEnable);
            registro += (int)sizeof(bool);

            EEPROM.writeBool(registro, resistivoEnable);
            registro += (int)sizeof(bool);

            EEPROM.writeBool(registro, controlOnOff);
            registro += (int)sizeof(bool);

            EEPROM.writeBool(registro, masterkeydone);
            registro += (int)sizeof(bool);

            EEPROM.writeUShort(registro, lastkey);
            registro += (int)sizeof(uint16_t);

            EEPROM.writeULong(registro, masterkey);

            EEPROM.commit();
#endif
            IEsp32::serial_println_shall(" == Stack updated == ");
        }

        void read()
        {
#ifdef DEPLOY
            int registro;
            registro = 0;

            ventilacionEnable = EEPROM.readBool(registro);
            registro += (int)sizeof(bool);

            resistivoEnable = EEPROM.readBool(registro);
            registro += (int)sizeof(bool);

            controlOnOff = EEPROM.readBool(registro);
            registro += (int)sizeof(bool);

            masterkeydone = EEPROM.readBool(registro);
            registro += (int)sizeof(bool);

            lastkey = EEPROM.readUShort(registro);
            registro += (int)sizeof(uint16_t);

            masterkey = EEPROM.readULong(registro);

            IEsp32::serial_println_shall(" == Stack read ==");
            print();
            IEsp32::serial_println_shall(" ================");
#endif
        }

        void print()
        {
            IEsp32::serial_print_shall("ventilacionEnable: "); IEsp32::serial_println_shall(ventilacionEnable);
            IEsp32::serial_print_shall("resistivoEnable: "); IEsp32::serial_println_shall(resistivoEnable);
            IEsp32::serial_print_shall("controlOnOff: "); IEsp32::serial_println_shall(controlOnOff);
            IEsp32::serial_print_shall("masterkeydone: "); IEsp32::serial_println_shall(masterkeydone);
            IEsp32::serial_print_shall("lastkey: "); IEsp32::serial_println_shall(lastkey);
            IEsp32::serial_print_shall("masterkey: "); IEsp32::serial_println_shall(masterkey);
        }
};
        



#endif