#ifndef __COMUNICACION
#define __COMUNICACION

#include "IEsp32.h"

class Comunicacion
{
    public:
        Comunicacion()
        {
            IEsp32::serial_println("Comunicacion: instance created");
        }

        static constexpr int sizecomand = 100;
        char comando[sizecomand];
        
        int longitud(const char *cadena);
        bool comparar(const char *cadena, const char *subcadena);
        bool compararEqual(const char *cadena, const char *subcadena);

        void send(const int page, const char* obj, double valor);
        void send(const char* obj);

        ~Comunicacion()
        {
            IEsp32::serial_println("Comunicacion: instance deleted");
        }
    
    private:
        void sendFinal();

};






#endif