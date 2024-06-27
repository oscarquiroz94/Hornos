#ifndef __MOTOR
#define __MOTOR

#include "Identity.h"
#include "IEsp32.h"

class Motor
{
    public:
        Motor(uint8_t tp) :
            running(IDENT::INVENTRUN, PIN_VENT_RUNNING),
            pinonoff(IDENT::OUTVENT, PIN_VENT_ONOFF)
        {
            type = tp;
            IEsp32::serial_print("Motor: instance created ");
            IEsp32::serial_println((uint16_t)type);
        }

        void on()  {pinonoff.high();}
        void off() {pinonoff.low();}

        void set_modes()
        {
            pinonoff.set_mode(PIN_VENT_ONOFF, OUTPUT);
            running.set_mode(PIN_VENT_RUNNING, INPUT);
        }

        bool isRunning(){return running.read();}

        ~Motor()
        {
            IEsp32::serial_println("Motor: instance deleted");
        }

    private:
        uint8_t   type;
        Entradas  running;
        Salidas   pinonoff;

        static constexpr uint8_t PIN_VENT_RUNNING  = 33;
        static constexpr uint8_t PIN_VENT_ONOFF    = 14;
};



#endif