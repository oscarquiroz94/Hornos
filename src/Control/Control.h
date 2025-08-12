#ifndef __CONTROL
#define __CONTROL

#include "../InterfazHardware/IEsp32.h"
#include "../Control/Operativos.h"
#include "../Utilidades/Temporizador.h"
#include "../Utilidades/MeanFilterLib.h"

class Control
{
    public:
        virtual void set_temperatura_deseada(double valor) { setpoint = valor; };

    protected:
        double setpoint = 0.0;
};

class ControlOnOff : public Control
{
    public:

        void regular(Operativos& op)
        {
            if (op.analogicos.tempera > setpoint + umbral) 
                op.eventos.onvalvula = false;

            else if (op.analogicos.tempera <= setpoint - umbral) 
                op.eventos.onvalvula = true;
        }

    protected:
        double umbral = 5.0;
};

class ControlOnOffpwm : public ControlOnOff
{
    public:

        double regular(Operativos& op)
        {
            if (op.analogicos.tempera > setpoint + umbral) 
                currentvalue = 0.0;

            else if (op.analogicos.tempera <= setpoint - umbral) 
                currentvalue = 100.0;
            
            return currentvalue;
        }

        bool isInsideUmbral(Operativos& op)
        {
            if (op.analogicos.tempera > setpoint - umbral && op.analogicos.tempera < setpoint + umbral) 
                return true;
            else
                return false;
        }
    
    private:
        double currentvalue = 0.0;
};

class ControlPid : public Control
{
    public:
        ControlPid() : 
            tc(false, true, TemposNames::PRESION_TC)
        {
            IEsp32::serial_println("ControlPid: instance created");
        }

        //Porcentaje de potencia quemador
        double regular(Operativos& op)
        {
            //pid.error = setpoint - emu.tempera;
            error = setpoint - op.analogicos.tempera;

            if (!windup) integral = integral + error*periodo;
            proporcional = error;
            derivativa = (error - error_ant) / periodo;
            accion = Kp*proporcional + Ki*integral + Kd*derivativa;
            error_ant = error;

            if (accion < min_accion || accion > max_accion) saturado = true;
            else saturado = false;

            if ((error < 0.0 && accion < 0.0) || (error > 0.0 && accion > 0.0)) igualsigno = true;
            else igualsigno = false;

            if (saturado && igualsigno) windup = true;
            else windup = false;

            if(accion > 100.0) accion = 100.0;
            if(accion <   0.0) accion =   0.0;

            IEsp32::serial_print_shall("Des: ");
            IEsp32::serial_print_shall(setpoint);
            IEsp32::serial_print_shall(" act: ");
            //IEsp32::serial_print_shall(emu.tempera);
            IEsp32::serial_print_shall(op.analogicos.tempera);
            IEsp32::serial_print_shall(" P: ");
            IEsp32::serial_print_shall(Kp*proporcional);
            IEsp32::serial_print_shall(" I: ");
            IEsp32::serial_print_shall(Ki*integral);
            IEsp32::serial_print_shall(" D: ");
            IEsp32::serial_println_shall(Kd*derivativa);

            IEsp32::serial_print_shall("Antiwdp: ");
            IEsp32::serial_print_shall(antiwindup());
            IEsp32::serial_print_shall(" error: ");
            IEsp32::serial_print_shall(abs(error));
            IEsp32::serial_print_shall(" deverr: ");
            IEsp32::serial_print_shall(abs(error - error_ant));
            IEsp32::serial_print_shall(" accion: ");
            IEsp32::serial_println_shall(accion);

            

            //emulador_planta();

            return accion;
        }

        

        ~ControlPid()
        {
            IEsp32::serial_println("ControlPid: instance deleted");
        }

    private:

        Temporizador tc;
        
        bool antiwdp = false;

        // struct Emulador
        // {
        //     double tempera = 0.0;
        //     double tempera_ant = 0.0;
        // } emu;

        
        const double Kp        =   1.0;
        const double Ki        =   0.005;
        const double Kd        =   0.05;
        double ganancia  =   5.0;
        double periodo   =   0.1;   //Muestreo digital
        double tao       =  50.0 / 5.0;   // T estable = 10 seg

        double accion = 0.0;
        double accion_ant = 0.0;
        double error = 0.0;
        double error_ant = 0.0;
        double integral = 0.0;
        double integral_ant = 0.0;
        double derivativa = 0.0;
        double proporcional = 0.0;

        double min_accion     = -100.0;
        double max_accion     = 100.0;
        bool   windup         = false;
        bool   saturado       = false;
        bool   igualsigno     = false;
        

        bool antiwindup()
        {
            //Si el error absoluto de temperatura no es cero(conservador)
            //Y el error absoluto no esta disminuyendo (filtro no es casi cero)
            //Entonces esperar tiempo de reaccion y activar antiwindup
            if (abs(error) > 3.0 && abs(error - error_ant) > 1.0 )
            {
                //Tiempo critico de no reaccion de la valvula
                if (tc.tiempo(5000)) 
                {
                    antiwdp = true;
                }
            }else 
            {
                antiwdp = false;
                tc.reset();
            }

            return antiwdp;
        }

        // void emulador_planta()
        // {
        //     emu.tempera = (pid.ganancia * pid.periodo / (2*pid.tao + pid.periodo)) * ( pid.accion + pid.accion_ant) + ((2*pid.tao - pid.periodo)/(2*pid.tao + pid.periodo))*emu.tempera_ant;
        //     emu.tempera_ant = emu.tempera;
        // }
};



#endif