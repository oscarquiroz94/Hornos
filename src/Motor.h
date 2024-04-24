#ifndef __MOTOR
#define __MOTOR

class Motor
{
    public:
        Motor(){}
        void on(){}
        void off(){}
        bool isRunning(){return running.read();}
        ~Motor(){}

    private:
        Entradas running;
};



#endif