#ifndef PUMPROTOCOL_H
#define PUMPROTOCOL_H

#include "message.h"
#include "globals.h"

class PUMProtocol
{
public:
    PUMProtocol();
    QByteArray pack(Message msg);
    Message unpack(QByteArray packed);

};

#endif // PUMPROTOCOL_H
