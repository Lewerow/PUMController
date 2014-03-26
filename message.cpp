#include "message.h"
#include <QXmlStreamReader>

CommunicationType getNextToken(QString& text);
bool isHexadecimal(unsigned char c);
bool isDecimal(unsigned char c);

QString convertBlanks(QString str)
{
    QString res;

    for(int i = 0; i < str.size(); i++)
    {
        unsigned char code = str[i].toLatin1();
        if(code < 33 || (code > 126 && code < 161))
        {
            res.append("\\");
            res.append(QString::number(code));
            res.append(" ");
        }
        else
            res.append(QChar(code));
    }

    return res;
}

Message::Message()
{
}

QString Message::report()
{
    QString result;
    result.append("\\");
    result.append(QString::number(address));
    result.append(" ");
    result.append("\\");
    result.append(QString::number(command));
    result.append(" ");
    result.append(convertBlanks(params));

    return result;
}

void Message::loadFromQString(QString textMsg)
{
    if(textMsg.size() < 2)
        return;

    address = getNextToken(textMsg);
    command = getNextToken(textMsg);

    while(textMsg.size() > 0)
        params.append(getNextToken(textMsg));
}

void Message::writeToXML(QXmlStreamWriter* xmlWriter)
{
    xmlWriter->writeStartElement(QString("message"));
    xmlWriter->writeTextElement(QString("address"), QString::number(address));
    xmlWriter->writeTextElement(QString("action"), QString::number(command));

    QString xmlParameters;
    for(int i = 0; i < params.size(); i++)
        xmlParameters.append(QString::number(params[i].toLatin1())+" ");

    xmlWriter->writeTextElement(QString("params"), xmlParameters.trimmed());
    xmlWriter->writeEndElement();
}

void Message::readFromXML(QXmlStreamReader* xmlReader)
{
    xmlReader->readNextStartElement();

    qDebug("Start message: ");
    qDebug(xmlReader->name().toLocal8Bit());
    xmlReader->readNextStartElement();
    address = xmlReader->readElementText().toShort();
    xmlReader->readNextStartElement();
    command = xmlReader->readElementText().toShort();

    xmlReader->readNextStartElement();

    QStringList xmlParameters = xmlReader->readElementText().split(" ");
    for(int i = 0; i < xmlParameters.size(); i++)
        params.append(QChar(xmlParameters[i].toShort()));

    xmlReader->readNext();
    qDebug("End message: ");
    qDebug(xmlReader->name().toLocal8Bit());
}

CommunicationType getNextToken(QString& text)
{
    if(text[0].toLatin1() != '\\' || text.size() == 1)
    {
        CommunicationType retVal = text[0].toLatin1();
        text.remove(0,1);
        return retVal;
    }

    // hexadecimal
    if(text.size() > 3 && text[1] == '0'&& text[2] == 'x')
    {
        QString hexadecimalNum;

        if(isHexadecimal(text[3].toLatin1()))
            hexadecimalNum.append(text[3]);

        else
        {
            text.remove(0,1);
            return '\\';
        }

        if(text.size() > 4 && isHexadecimal(text[4].toLatin1()))
            hexadecimalNum.append(text[4]);


        bool conversionOk;
        char retVal = hexadecimalNum.toUShort(&conversionOk, 16);

        if(conversionOk)
        {
            text.remove(0,3+hexadecimalNum.size());
            if(text.size() > 0 && text[0] == ' ')
                text.remove(0,1);

            return retVal;
        }

        else
        {
            text.remove(0,1);
            return '\\';
        }
    }



    // decimal
    QString decimalNum;
    for(int i = 1; i < 5 && i < text.size() && isDecimal(text[i].toLatin1()); i++)
        decimalNum.append(text[i]);

    if(decimalNum.size() == 0)
    {
        text.remove(0,1);
        return '\\';
    }

    bool conversionOk;
    CommunicationType retVal;
    unsigned short temp = decimalNum.toUShort(&conversionOk);
    if(conversionOk)
    {
        text.remove(0,1+decimalNum.size());
        if(temp > 255)
        {
            retVal = temp/10;
            text.prepend(QString::number(temp % 10));
            return retVal;
        }
        else
        {
            text = text.trimmed();
            retVal = temp;
            return retVal;
        }
    }
    else
    {
        text.remove(0,1);
        return '\\';
    }

}

bool isHexadecimal(unsigned char c)
{
    if( c >= 'A' && c <= 'F')
        return true;

    if( c >= 'a' && c <='f')
        return true;

    if(isDecimal(c))
        return true;

    return false;
}

bool isDecimal(unsigned char c)
{
    if(c >= '0' && c <= '9')
        return true;

    return false;
}
