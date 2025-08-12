#ifndef __TEMPORIZADOR
#define __TEMPORIZADOR

#include "../InterfazHardware/IEsp32.h"

class Temporizador {
    public:
        //false, true para iniciar contador desde cero y ejecutar accion
        //true, true para ejecutar accion y luego iniciar contador para otra ejecucion
        //false, false solo iniciar timer despues de darle vida
        //true, false sin efecto
        Temporizador(bool run, bool en, uint8_t name) : 
        _running(run), _enable(en), _name(name)
        {
            IEsp32::serial_print("Temporizador instance created: ");
            IEsp32::serial_println(name);
        }

        Temporizador(bool run, bool en) : 
          _running(run), _enable(en) {}

        virtual inline bool tiempo(unsigned long time){
            if(!_running && _enable) {
                _contador = IEsp32::millisec();
                _running = true;
            }
            if(IEsp32::millisec() - _contador >= time && _running && _enable){
                _running = false;
                return true;
            }
            return false;
        }
        inline void kill() {_enable = false; _running = false;}
        inline void alive() {_enable = true;}
        inline bool getRun() { return _running;}
        inline uint8_t get_name() {return _name;}
        inline void reset() {_contador = IEsp32::millisec();}
        inline unsigned long get_time() 
        {
          if (_running) return IEsp32::millisec() - _contador;
          else return 0L;
        }
        
        ~Temporizador()
        {
            IEsp32::serial_println("Temporizador: instance deleted");
        }

    protected:

        bool _running;
        bool _enable;
        uint8_t _name = 0;
        unsigned long _contador = 0L;
};

class TemporizadorMicro : public Temporizador
{
  public:
    TemporizadorMicro(bool run, bool en, uint8_t name) : Temporizador(run, en, name) {}
    TemporizadorMicro(bool run, bool en) : Temporizador(run, en) {}

    inline bool tiempo(unsigned long time){
      if(!_running && _enable) {
        _contador = IEsp32::microsec();
        _running = true;
      }
      if(IEsp32::microsec() - _contador >= time && _running && _enable){
        _running = false;
        return true;
      }
      return false;
    }

    ~TemporizadorMicro(){}
};



#endif