#include "Main.h"
#include "IEsp32.h"
#include "Manager.h"
#include "Supervision.h"

Debug       dbg;
Horno       horno;
Manager     manager;
Supervision supervisor;

InterfazInputs interinputs;
Operativos op_aux;

#ifndef DEPLOY
    #define SERIAL_PORT_NX "\\\\.\\COM15"   
    SeriaLib serial_nxcom(SERIAL_PORT_NX, 115200);
#else
    #include <EEPROM.h>
#endif

extern void serialEvent();
extern void serial2Event();

#if defined(DEPLOY) && !defined(INTEGRATED_TEST)
void setup()
{
    EEPROM.begin(sizeof(Stack));
#else
void setupmain()
{
#endif

    IEsp32::serial_begin(115200);
    IEsp32::serial2_begin(115200, 0x800001c, 16, 17);
    IEsp32::serial_println_shall();


#ifdef OVERRIDE_STACK
    horno.get_instance_stack().save();
#endif
    horno.get_instance_stack().read();

    horno.set_modes();
    horno.get_instance_nextion().reset();
    IEsp32::retardo(2000);

    //if (horno.get_instance_stack().masterkeydone)
    //{
        horno.get_instance_nextion().com.send("page 0");
    //}

    horno.get_instance_nextion().send_stack
        (horno.get_instance_op(), horno.get_instance_stack());

}

#if defined(DEPLOY) && !defined(INTEGRATED_TEST)
void loop()
{
    if (IEsp32::serial2_available()) serial2Event();
    if (IEsp32::serial_available()) serialEvent();
    
    manager.run(horno);
    supervisor.verify_all(horno);
    
    dbg.interprete(horno.get_instance_op());


    IEsp32::retardo(200);
    IEsp32::serial_println("======================");
}
#else
void loopmain()
{
    manager.run(horno);
    supervisor.verify_all(horno);

    //Recibir de Nextion
    if (serial_nxcom.available()) 
    {
        serial_nxcom.readString(horno.get_instance_nextion().com.comando, '\n', Comunicacion::sizecomand, 30);
        IEsp32::serial_print("FROM NX -> ");
        IEsp32::serial_println(horno.get_instance_nextion().com.comando);
    }
    
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(100));
    IEsp32::serial_println("======================");
    
}
#endif

#ifndef DEPLOY
//Taken from https://gist.github.com/vmrob/ff20420a20c59b5a98a1 VMROB
int main() {
    std::condition_variable cv;
    std::mutex mutex;
    std::deque<std::string> lines; // protected by mutex

    setupmain();

    // thread to read from stdin
    std::thread io{[&]{
        std::string tmp;
        while (true) {
            std::getline(std::cin, tmp);
            std::lock_guard lock{mutex};
            lines.push_back(std::move(tmp));
            cv.notify_one();
        }
    }};

    // the nonblocking thread
    std::deque<std::string> toProcess;
    while (true) {
        {
            // critical section
            std::unique_lock lock{mutex};
            if (cv.wait_for(lock, std::chrono::seconds(0), [&]{ return !lines.empty(); })) {
                // get a new batch of lines to process
                std::swap(lines, toProcess);
            }
        }
        if (!toProcess.empty()) {
            //std::cout << "processing new lines..." << std::endl;
            for (auto&& line : toProcess) {
                // process lines received by io thread
                //std::cout << line << std::endl;
                strcpy(Debug::com.comando, line.data());

                if (!Debug::com.compararEqual(Debug::com.comando, ""))
                {
                    IEsp32::serial_print_shall("FROM DEBUG -> "); 
                    IEsp32::serial_println_shall(Debug::com.comando);
                }

                dbg.interprete(op_aux);
            }
            toProcess.clear();
        }

        loopmain();

        //std::this_thread::sleep_for(std::chrono::milliseconds(100));
        //std::cout << "waiting..." << std::endl;
    }
    io.join();
    serial_nxcom.closeDevice();
}
#endif
