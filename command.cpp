#include "command.h"

Command::Command()
{
}

void Command::writeToXML(QXmlStreamWriter* xmlWriter)
{
    xmlWriter->writeStartElement(QString("command"));
    xmlWriter->writeTextElement(QString("name"), msgName);
    msg.writeToXML(xmlWriter);
    xmlWriter->writeEndElement();
}

void Command::readFromXML(QXmlStreamReader* xmlReader)
{
    xmlReader->readNextStartElement();
    qDebug("Start command: ");
    qDebug(xmlReader->name().toLocal8Bit());
    xmlReader->readNextStartElement();
    msgName = xmlReader->readElementText();
    msg.readFromXML(xmlReader);
    xmlReader->readNext();
    qDebug("End command: ");
    qDebug(xmlReader->name().toLocal8Bit());
}
