#ifndef PUMCOMMUNICATION_H
#define PUMCOMMUNICATION_H

using namespace std;

#include <QIODevice>
#include <QThread>
#include "pumprotocol.h"
#include "globals.h"

class PUMCommunication : public QObject
{
    Q_OBJECT
public:
    PUMCommunication();
    virtual ~PUMCommunication();

    virtual void close();
    virtual void open();
    virtual bool isValid() = 0;

    virtual QIODevice* getPort()
        {return commDevice;}

    virtual void logIt(Message msg, bool isReceived = false);
    virtual void logIt(QString str);

    QString getDeviceName()
        {return deviceName;}

    const DeviceAddress controlAddress = 48;

public slots:

    virtual Message read();
    virtual qint64 write(Message toWrite);

signals:
    void messageSent(Message);
    void messageReceived(Message);

protected:
    QIODevice* commDevice;
    QString deviceName;
    QThread localThread;

    QString protocolName;
    PUMProtocol* protocol;
    QFile* log;
    QVector<Message> inputLog;
    QVector<Message> outputLog;

    virtual void waitForData() = 0;
};

#endif // PUMCOMMUNICATION_H
