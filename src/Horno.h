#ifndef __HORNO
#define __HORNO

#include "Identity.h"
#include "IEsp32.h"
#include "Quemador.h"
#include "Motor.h"
#include "Control.h"
#include "Operativos.h"
#include "Nextion.h"
#include "Entradas.h"
#include "Salidas.h"
#include "Baliza.h"
#include "Debug.h"

class Horno
{
    public:
        Horno() :
            termostato(IDENT::TERMOSTATO, PIN_TERMOSTATO),
            valvula(IDENT::OUTVALVULA, PIN_VALVULA_ONOFF),
            sensTempera(IDENT::SENSTEMPERA, PIN_SCLK, PIN_CS1, PIN_MISO),
            sensTemperaAux(IDENT::SENSTEMPAUX, PIN_SCLK, PIN_CS2, PIN_MISO)
        {
            IEsp32::serial_println("Horno: instance created");
        }

        Operativos& get_instance_op()         {return op;}
        Stack&      get_instance_stack()      {return st;}
        
        Nextion&    get_instance_nextion()    {return nx;}
        Entradas&   get_instance_termostato() {return termostato;}
        Salidas&    get_instance_valvula()    {return valvula;}
        Baliza&     get_instance_baliza()     {return baliza;}
        
        SensorAnalogico& get_instance_sensTempera()    {return sensTempera;} 
        SensorAnalogico& get_instance_sensTemperaAux() {return sensTemperaAux;} 

        //ToDo: mover a factories
        Control*  get_instace_controlador()
        {
            if (st.controlOnOff)
            {
                static ControlOnOff controlador;
                return &controlador;
            }else
            {
                return nullptr;
            }
        }

        Motor* get_instance_motor()
        {
            if (st.ventilacionEnable)
            {
                static Motor ventilador(IDENT::VENTILADOR);
                return &ventilador;
            }else
            {
                return nullptr;
            }
        }

        Quemador* get_instance_quemador()   
        {
            if (st.resistivoEnable)
            {
                static QuemadorResistivo quemador(IDENT::QUEMRESIST);
                return &quemador;
            }else
            {
                static Quemador quemador(IDENT::QUEMADOR);
                return &quemador;
            }
            
        }

        void set_modes()
        {
            get_instance_quemador()->set_modes();
            get_instance_motor()->set_modes();
            get_instance_baliza().set_modes();
            valvula.set_mode(PIN_VALVULA_ONOFF, OUTPUT);
            termostato.set_mode(PIN_TERMOSTATO, INPUT);
        }

        ~Horno()
        {
            IEsp32::serial_println("Horno: instance deleted");
        }
    
    private:
        Operativos op;
        Stack      st;
        ControlPid pid;
        Nextion    nx;
        Entradas   termostato;  
        Salidas    valvula;
        Baliza     baliza;
        SensorAnalogico  sensTempera;
        SensorAnalogico  sensTemperaAux;

        static constexpr uint8_t PIN_SCLK = 18;
        static constexpr uint8_t PIN_CS1  =  5;
        static constexpr uint8_t PIN_CS2  =  4;
        static constexpr uint8_t PIN_MISO = 19;
        static constexpr uint8_t PIN_TERMOSTATO    = 32;
        static constexpr uint8_t PIN_VALVULA_ONOFF = 12;
};


#endif