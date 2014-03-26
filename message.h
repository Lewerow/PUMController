#ifndef MESSAGE_H
#define MESSAGE_H

#include "globals.h"

class Message
{
public:
    Message();
    Message(QString str)
    {loadFromQString(str);}

    DeviceAddress address;
    CommandType command;

    QString params;

    QString report();
    void loadFromQString(QString textMsg);

    void writeToXML(QXmlStreamWriter* xmlWriter);
    void readFromXML(QXmlStreamReader* xmlReader);

};

Q_DECLARE_METATYPE(Message)

#endif // MESSAGE_H
