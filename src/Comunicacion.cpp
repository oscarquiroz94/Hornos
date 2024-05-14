#include "Comunicacion.h"
#include "IEsp32.h"

void serial2Event()
{

}

int Comunicacion::longitud(const char *cadena)
{
    int i = 0;
    while(cadena[i] != '\0' && cadena[i] != '\r' && cadena[i] != '\n') i++;
    return i;
}

bool Comunicacion::comparar(const char *cadena, const char *subcadena)
{
    for(int i=0; i < longitud(subcadena); i++){
        if(cadena[i] != subcadena[i]) 
            return false;
    }
    return true;
}

bool Comunicacion::compararEqual(const char *cadena, const char *subcadena)
{
    if(longitud(cadena) != longitud(subcadena)) 
        return false;

    for(int i=0; i < longitud(subcadena); i++){
        if(cadena[i] != subcadena[i]) 
            return false;
    }
    return true;
}

void Comunicacion::send(const char* obj)
{
    IEsp32::serial2_print(obj);
    sendFinal();
}

void Comunicacion::send(const int page, const char* obj, double valor)
{
 #ifdef SHOWNEXTION
    IEsp32::serial_print(F("TO NX -> "));
#endif
    //extraerFromPTSR(obj);
#ifdef DEPLOY
    //String cadena = "page" + String(page) + "." + _memo + ".val=" + String((int)valor);
    String cadena = "page" + String(page) + "." + obj + ".val=" + String((int)valor);
#else
    //std::string cadena = "page" + std::to_string(page) + "." + _memo + ".val=" + std::to_string((int)valor);
    std::string cadena = "page" + std::to_string(page) + "." + obj + ".val=" + std::to_string((int)valor);
#endif
    send(&cadena[0]);
}

void Comunicacion::sendFinal()
{
    IEsp32::serial2_write(0xff);
    IEsp32::serial2_write(0xff);
    IEsp32::serial2_write(0xff);
#ifdef SHOWNEXTION
    IEsp32::serial_println();
#endif
    IEsp32::retardo(3);
}