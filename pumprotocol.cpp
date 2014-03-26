#include "pumprotocol.h"

PUMProtocol::PUMProtocol()
{
}

QByteArray PUMProtocol::pack(Message msg)
{
    QByteArray result;

    result.append(0xff);
    result.append(msg.address);
    result.append(msg.command);
    result.append(msg.params);
    result.append(0x0a);

    return result;
}

Message PUMProtocol::unpack(QByteArray packed)
{
    Message msg;

    if(packed.startsWith(START_SYMBOL) && packed.endsWith(END_SYMBOL))
    {
        msg.address = (DeviceAddress)packed.at(1);
        msg.command = (CommandType) packed.at(2);
        msg.params = QString(packed.mid(3,packed.length()-4));
    }

    else
        throw InvalidPackage;

    return msg;
}
