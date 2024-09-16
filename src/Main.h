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
//#define EMULATION
#define DEPLOY

//***********************************************************

#ifdef EMULATION
#define EXTERNAL_INTERFACES
#endif

#ifdef DEPLOY
//#define INTEGRATED_TEST
#endif


//! *********************************************************

#define OVERRIDE_STACK

//! *********************************************************

//#define SHOW_IO
#define DEBUG_INFO
//#define SHOWNEXTION
#define CONFIRM_AVAILABLE //Las confirmaciones estan disponibles


//************************************************************
//* COMANDOS NEXTION
// BURNER
// FAN
// VALVE
// STOPRAMPA
// RUNTIMER
// SETPOINT,150
// TIMERAMP,100
// TIMER,50
// ISBURNER
// ISNBURNER
// ISFAN
// ISNFAN
// ISTERMO
// ISNTERMO
// ISALARM
// ISNALARM



