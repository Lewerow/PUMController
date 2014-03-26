#ifndef COMMAND_H
#define COMMAND_H

#include "message.h"

class Command
{
public:
    Command();

    QString getName()
    {return msgName;}

    Message getMsg()
    {return msg;}

    void setName(QString nName)
    {msgName = nName;}
    void setMsg(Message nMsg)
    {msg = nMsg;}

    void writeToXML(QXmlStreamWriter* xmlWriter);
    void readFromXML(QXmlStreamReader* xmlReader);

protected:
    Message msg;
    QString msgName;
};

#endif // COMMAND_H
