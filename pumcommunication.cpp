#include "pumcommunication.h"

PUMCommunication::PUMCommunication()
{
    this->moveToThread(&localThread);
    localThread.start();
    log = new QFile("log.log");
    log->open(QIODevice::Append | QIODevice::Unbuffered);
}

PUMCommunication::~PUMCommunication()
{
    log->close();
    localThread.exit(0);
    delete log;
}

void PUMCommunication::logIt(Message msg, bool isReceived)
{
    if(log->isWritable())
    {
        QString logged = "";
        logged.append((isReceived) ? "(RECEIVED) " : "(SENT) ");
        logged.append(QDateTime::currentDateTime().toString("hh:mm dd/mm/yyyy"));
        logged.append(msg.report());
        log->write(logged.toLocal8Bit());
    }

    if(msg.address == controlAddress)
        inputLog.push_back(msg);
    else
        outputLog.push_back(msg);

}

void PUMCommunication::logIt(QString str)
{
    if(log->isWritable())
    {
        log->write(QDateTime::currentDateTime().toString("hh:mm dd/mm/yyyy").toLocal8Bit());
        log->write(str.toLocal8Bit());
        log->write("\n");
        log->flush();
    }
}

Message PUMCommunication::read()
{
    Message resultMsg;

    if(!commDevice->isOpen())
        return resultMsg;

    while(commDevice->bytesAvailable() > 0)
    {
        QByteArray readBytes;

        while(commDevice->bytesAvailable() > 0)
        {
            readBytes.append(commDevice->read(1));

            if(readBytes.endsWith(END_SYMBOL))
                break;

            if(commDevice->bytesAvailable() == 0 && !readBytes.endsWith(END_SYMBOL))
                this->waitForData();
        }

        try
        {
            if(readBytes.size() > 1)
            {
                resultMsg = protocol->unpack(readBytes);
                emit messageReceived(resultMsg);
                logIt(resultMsg, true);
            }
        }
        catch(...)
        {
            logIt("Error during transmission: " + readBytes);
            qDebug((QString("Error during transmission: "+readBytes).toLocal8Bit()));
        }

    }

    return resultMsg;
}

qint64 PUMCommunication::write(Message toWrite)
{
    logIt(toWrite, false);

    read();
    qint64 bytesWritten = commDevice->write(protocol->pack(toWrite));

    if(bytesWritten != -1)
        emit messageSent(toWrite);

    else
        qDebug ((QString("No bytes written. Message: ")+ protocol->pack(toWrite)).toLocal8Bit());

    return bytesWritten;
}

void PUMCommunication::close()
{
    if(commDevice != NULL)
    {
        if(commDevice->isOpen())
            commDevice->close();
        commDevice = NULL;
    }
}
void PUMCommunication::open()
{
    if(commDevice == NULL)
        throw NoCommunicationPort;

    if(!commDevice->isOpen())
        commDevice->open(QIODevice::ReadWrite | QIODevice::Unbuffered);
}
