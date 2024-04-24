#ifndef __QUEMADOR
#define __QUEMADOR

class Quemador
{
    public:
        Quemador(){}
        void on(){}
        void off(){}
        bool is_running() {return running.read();}
        bool is_alarma()  {return alarma.read();}
        ~Quemador(){}

    private:
        Entradas running;
        Entradas alarma;
};

#endif