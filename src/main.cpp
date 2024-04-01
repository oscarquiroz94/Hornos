#include "Main.h"

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

}
#else
void loopmain()
{

}
#endif

#ifndef DEPLOY
int main(void)
{
    setupmain();
    loopmain();
}
#endif
