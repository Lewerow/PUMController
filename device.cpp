#include "device.h"

Device::Device()
{
}

void Device::writeToXML(QXmlStreamWriter* xmlWriter)
{
    xmlWriter->writeStartElement(QString("device"));
    xmlWriter->writeTextElement(QString("name"), name);
    xmlWriter->writeTextElement(QString("address"), QString::number(address));
    xmlWriter->writeTextElement(QString("type"), name);
    xmlWriter->writeTextElement(QString("class"), name);

    for(vector<DeviceParameter>::iterator param = params.begin(); param != params.end(); param++)
        (*param).writeToXML(xmlWriter);

    xmlWriter->writeEndElement();
}

void Device::readFromXML(QXmlStreamReader* xmlReader)
{
    xmlReader->readNextStartElement();

}
