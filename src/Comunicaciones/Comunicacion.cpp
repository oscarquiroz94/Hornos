#include "Comunicacion.h"
#include "Debug.h"


#ifdef DEPLOY
//* Eventos seriales de Nextion
void serial2Event()
{
    uint8_t i=0;
    char caracter;
    while (IEsp32::serial2_available()){
        caracter = IEsp32::serial2_read();
        
        if (!isAlphaNumeric(caracter) && caracter != ','){continue;}

        if(i < (uint8_t)(sizeof(Nextion::com.comando)/sizeof(Nextion::com.comando[0]))-1)
        {
            Nextion::com.comando[i] = caracter;
            i++;
        }
        if(caracter == '\0')break;
        IEsp32::retardo(2);
    }
    
    //Importante para la logica
    Nextion::com.comando[i] = '\n';

    if (!Nextion::com.compararEqual(Nextion::com.comando, ""))
    {
        IEsp32::serial_print_shall("FROM NX -> "); 
        IEsp32::serial_println_shall(Nextion::com.comando);
    }
}

//* Eventos seriales de debug
void serialEvent()
{
    uint8_t i=0;
    char caracter;
    while (IEsp32::serial_available()){
        caracter = IEsp32::serial_read();
        
        if (!isAlphaNumeric(caracter) && caracter != ','){continue;}

        if(i < (uint8_t)(sizeof(Debug::com.comando)/sizeof(Debug::com.comando[0]))-1)
        {
            Debug::com.comando[i] = caracter;
            i++;
        }
        if(caracter == '\0')break;
        IEsp32::retardo(2);
    }
    
    //Importante para la logica
    Debug::com.comando[i] = '\n';

    if (!Debug::com.compararEqual(Debug::com.comando, ""))
    {
        IEsp32::serial_print_shall("FROM DEBUG -> "); 
        IEsp32::serial_println_shall(Debug::com.comando);
    }
}

#endif

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

    IEsp32::retardo(3);
}