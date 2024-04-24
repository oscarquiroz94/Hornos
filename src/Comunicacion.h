#ifndef __COMUNICACION
#define __COMUNICACION

class Comunicacion
{
    public:
        Comunicacion(){}
        void send(const char* comando)
        {
            Serial.print(comando);
        }
        ~Comunicacion(){}
};



#endif