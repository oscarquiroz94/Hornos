/*!
\file    SeriaLib.h
\brief   Header file of the class SeriaLib. This class is used for communication over a serial device.
\author  Philippe Lucidarme (University of Angers)
\version 2.0
\date    december the 27th of 2019
This Serial library is used to communicate through serial port.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE X CONSORTIUM BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

This is a licence-free software, it can be used by anyone who try to build a better world.
*/

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#ifndef SERIALIB_H
#define SERIALIB_H


/*! To avoid unused parameters */
#define UNUSED(x) (void)(x)

/**
 * number of serial data bits
 */
enum SerialDataBits {
    SERIAL_DATABITS_5, /**< 5 databits */
    SERIAL_DATABITS_6, /**< 6 databits */
    SERIAL_DATABITS_7, /**< 7 databits */
    SERIAL_DATABITS_8,  /**< 8 databits */
    SERIAL_DATABITS_16,  /**< 16 databits */
};

/**
 * number of serial stop bits
 */
enum SerialStopBits {
    SERIAL_STOPBITS_1, /**< 1 stop bit */
    SERIAL_STOPBITS_1_5, /**< 1.5 stop bits */
    SERIAL_STOPBITS_2, /**< 2 stop bits */
};

/**
 * type of serial parity bits
 */
enum SerialParity {
    SERIAL_PARITY_NONE, /**< no parity bit */
    SERIAL_PARITY_EVEN, /**< even parity bit */
    SERIAL_PARITY_ODD, /**< odd parity bit */
    SERIAL_PARITY_MARK, /**< mark parity */
    SERIAL_PARITY_SPACE /**< space bit */
};


class SeriaLib
{
public:

    SeriaLib (const char *device, unsigned int bauds);
    ~SeriaLib();

    char openDevice(const char *Device, 
                    const unsigned int Bauds,
                    SerialDataBits Databits = SERIAL_DATABITS_8,
                    SerialParity   Parity = SERIAL_PARITY_NONE,
                    SerialStopBits Stopbits = SERIAL_STOPBITS_1);

    bool isDeviceOpen();
    void closeDevice();

    int writeChar(char);
    int readChar(char* pByte, const unsigned int timeOut_ms=0);

    int writeString (const char *String);
    int readString (char *receivedString,
                    char  finalChar,
                    unsigned int maxNbBytes,
                    const unsigned int timeOut_ms=0);

    int writeBytes(const void *Buffer, 
                    const unsigned int NbBytes);

    int readBytes(void *buffer,
                unsigned int maxNbBytes,
                const unsigned int timeOut_ms=0, 
                unsigned int sleepDuration_us=100);


    char flushReceiver();
    bool available();

    bool DTR(bool status);
    bool setDTR();
    bool clearDTR();

    bool RTS(bool status);
    bool setRTS();
    bool clearRTS();

    bool isRI();
    bool isDCD();
    bool isCTS();
    bool isDSR();
    bool isRTS();
    bool isDTR();


private:

    int readStringNoTimeOut(char *String,char FinalChar,unsigned int MaxNbBytes);

    bool currentStateRTS;
    bool currentStateDTR;

    HANDLE        hSerial;
    COMMTIMEOUTS  timeouts;

};


class timeOut
{
    public:

        timeOut();

        void initTimer();
        unsigned long int elapsedTime_ms();

    private:
        struct timeval previousTime;
};

#endif // serialib_H