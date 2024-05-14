//**********************************************************

// Build the atmega project environment
// just for deployment
//* $ pio run -e atmega

// Build the test project if you are
// testing o emulating
//* $ pio run -e test
//* execute .pip\build\test\program.exe

//***********************************************************

//#define UNIT_TEST
#define EMULATION
//#define DEPLOY

//***********************************************************

#ifdef EMULATION
#define EXTERNAL_INTERFACES
#endif

#ifdef DEPLOY
//#define INTEGRATED_TEST
#endif


//************************************************************


#define SHOW_IO
#define OUTFROM_CONSOLE