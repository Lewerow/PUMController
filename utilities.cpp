#include <QString>
#include "QExtSerialPort1.2RC/src/qextserialport.h"

QString baudRateToText(BaudRateType bRate)
{
    /*
    QString sBaudRate;
    switch(bRate)
    {
    case BAUD110:
        sBaudRate = "110";
        break;
    case BAUD300:
        sBaudRate = "300";
        break;
    case BAUD600:
        sBaudRate = "600";
        break;
    case BAUD1200:
        sBaudRate = "1200";
        break;
    case BAUD2400:
        sBaudRate = "2400";
        break;
    case BAUD4800:
        sBaudRate = "4800";
        break;
    case BAUD9600:
        sBaudRate = "9600";
        break;
    case BAUD19200:
        sBaudRate = "19200";
        break;
    case BAUD38400:
        sBaudRate = "38400";
        break;
    case BAUD57600:
        sBaudRate = "57600";
        break;
    case BAUD115200:
        sBaudRate = "115200";
        break;
    default:
        sBaudRate = "9600";
    }
    */

    return QString::number(bRate);
}

QString parityToText(ParityType bPar)
{
    QString sParity;

    switch(bPar)
    {
        case PAR_EVEN:
            sParity = "EVEN";
            break;
        case PAR_ODD:
            sParity = "ODD";
            break;
        default:
            sParity = "NONE";
    }

    return sParity;
}

QString stopBitsToText(StopBitsType bSTB)
{
    QString sSBTS;
    switch(bSTB)
    {
        case STOP_1:
            sSBTS = "1";
            break;
        default:
            sSBTS = "2";
            break;
    }

    return sSBTS;
}

QString dataBitsToText(DataBitsType bDAB)
{
    QString sDBTS;
    switch(bDAB)
    {
        case DATA_5:
            sDBTS = "5";
            break;
        case DATA_6:
            sDBTS = "6";
            break;
        case DATA_7:
            sDBTS = "7";
            break;
        default:
            sDBTS = "8";
            break;
    }

    return sDBTS;
}
