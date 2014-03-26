#include "rs232port.h"

RS232Port::RS232Port(QextSerialPort* device) :
    PUMCommunication()
{
    commDevice = device;
    deviceName = "RS232";
    connect(commDevice,SIGNAL(readyRead()),this,SLOT(read()));
}

RS232Port::~RS232Port()
{
    if(commDevice == NULL)
    {}

    else
    {
        if(commDevice->isOpen())
            commDevice->close();
        delete commDevice;

        commDevice = NULL;
    }
}

bool RS232Port::isValid()
{
    if(commDevice == NULL)
        return false;

    if(!(commDevice->isWritable() && commDevice->isReadable()))
        return false;

    return true;
}

void RS232Port::waitForData()
{
    QextSerialPort* port = static_cast<QextSerialPort*>(commDevice);
    int baudRate = port->baudRate();
    int oneByteTransmissionTime = baudRate/(1000000*8);
    int sleepTime = 4*oneByteTransmissionTime; // czekamy profilaktycznie na 4 bajty

    QThread::currentThread()->usleep(sleepTime);
}

