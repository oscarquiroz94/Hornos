#ifndef __CONTROL
#define __CONTROL

#include "IEsp32.h"
#include "Temporizador.h"

class Control
{
    public:
        Control() : 
            tc(false, true, TemposNames::PRESION_TC)
        {
            IEsp32::serial_println("Control: instance created");
        }

        void set_temperatura_deseada(double valor){ setpoint = valor; }

        //Porcentaje de potencia quemador
        double regular()
        {
            //! Por el momento se usa temperatura emulada que empieza en cero
            pid.error = setpoint - emu.tempera;

            IEsp32::serial_print_shall("Deseada: ");
            IEsp32::serial_print_shall(setpoint);
            IEsp32::serial_print_shall(" actual: ");
            IEsp32::serial_print_shall(emu.tempera);
            IEsp32::serial_print_shall(" accion: ");
            IEsp32::serial_println_shall(accion);

            IEsp32::serial_print_shall("Antiwdp: ");
            IEsp32::serial_print_shall(antiwindup());
            IEsp32::serial_print_shall(" error: ");
            IEsp32::serial_print_shall(abs(pid.error));
            IEsp32::serial_print_shall(" deverr: ");
            IEsp32::serial_println_shall(abs(pid.error - pid.error_ant));

            if(!antiwindup())
            {
                pid.proporcional = pid.Kp * pid.error;
                pid.integral     = pid.integral + pid.Ki * pid.error * pid.periodo;
                pid.derivativa   = pid.Kd * (pid.error - pid.error_ant) / pid.periodo;
                pid.accion       = pid.proporcional + pid.integral + pid.derivativa;
                pid.error_ant    = pid.error;

                accion = pid.accion;
            }else
            {
                accion = 0.0;
            }

            if(accion > 100.0) accion = 100.0;
            if(accion <   0.0) accion =   0.0;

            

            emulador_planta();



            return accion;
        }

        

        ~Control()
        {
            IEsp32::serial_println("Control: instance deleted");
        }

    private:

        Temporizador tc;
        double setpoint;
        bool antiwdp;
        double accion;

        struct Emulador
        {
            double tempera = 0.0;
            double tempera_ant = 0.0;
        } emu;

        struct PID
        {
            const double Kp        =   0.4;
            const double Ki        =   0.04;
            const double Kd        =   1.0;
            const double ganancia  =   5.0;
            const double periodo   =   0.1;   //Muestreo digital
            const double tao       =  50.0 / 5.0;   // T estable = 10 seg

            double accion = 0.0;
            double accion_ant = 0.0;
            double error = 0.0;
            double error_ant = 0.0;
            double integral = 0.0;
            double integral_ant = 0.0;
            double derivativa = 0.0;
            double proporcional = 0.0;
        } pid;

        bool antiwindup()
        {
            //Si el error absoluto de temperatura no es cero(conservador)
            //Y el error absoluto no esta disminuyendo (derivada no es casi cero)
            //Entonces esperar tiempo de reaccion y activar antiwindup
            if (abs(pid.error) > 3.0 && abs(pid.error - pid.error_ant) <= 0.01 )
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

        void emulador_planta()
        {
            emu.tempera = (pid.ganancia * pid.periodo / (2*pid.tao + pid.periodo)) * ( pid.accion + pid.accion_ant) + ((2*pid.tao - pid.periodo)/(2*pid.tao + pid.periodo))*emu.tempera_ant;
            emu.tempera_ant = emu.tempera;
        }
};



#endif