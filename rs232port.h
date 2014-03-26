#ifndef RS232PORT_H
#define RS232PORT_H

#include "pumcommunication.h"
#include "qextserialport.h"

class RS232Port : public PUMCommunication
{
public:
    RS232Port(QextSerialPort* );
    virtual ~RS232Port();
    virtual bool isValid();

protected:
    virtual void waitForData();

private:
    unsigned int timeout;

};

#endif // RS232PORT_H
