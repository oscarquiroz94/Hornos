#include "Main.h"

#include "Manager.h"
#include "Supervision.h"

Horno       horno;
Manager     manager;
Supervision supervisor;

#if defined(DEPLOY) && !defined(INTEGRATED_TEST)
void setup()
#else
void setupmain()
#endif
{

}

#if defined(DEPLOY) && !defined(INTEGRATED_TEST)
void loop()
{
    manager.run(horno);
    supervisor.verify_all(horno);
}
#else
void loopmain()
{
    manager.run(horno);
    supervisor.verify_all(horno);

    Esp32::serial_println("======================");

    manager.run(horno);
    supervisor.verify_all(horno);

    Esp32::serial_println("======================");
}
#endif

#ifndef DEPLOY
int main(void)
{
    setupmain();
    loopmain();
}
#endif
