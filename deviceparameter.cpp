#include "deviceparameter.h"

DeviceParameter::DeviceParameter()
{
}

void DeviceParameter::writeToXML(QXmlStreamWriter* xmlWriter)
{
    xmlWriter->writeStartElement("param");

    xmlWriter->writeTextElement(QString("name"), name);
    xmlWriter->writeTextElement(QString("unit"), unit);
    xmlWriter->writeTextElement(QString("max"), QString::number(max));
    xmlWriter->writeTextElement(QString("min"), QString::number(min));
    xmlWriter->writeTextElement(QString("step"), QString::number(step));
    xmlWriter->writeTextElement(QString("value"), QString::number(value));

    xmlWriter->writeEndElement();

    if(xmlWriter->hasError())
        throw ParseError;
}

void DeviceParameter::readFromXML(QXmlStreamReader* xmlReader)
{
    bool okMax, okMin, okStep, okVal;

    xmlReader->readNextStartElement();
    xmlReader->readNextStartElement();
    name = xmlReader->readElementText();
    xmlReader->readNextStartElement();
    unit = xmlReader->readElementText();
    xmlReader->readNextStartElement();
    max = xmlReader->readElementText().toDouble(&okMax);
    xmlReader->readNextStartElement();
    min = xmlReader->readElementText().toDouble(&okMin);
    xmlReader->readNextStartElement();
    step = xmlReader->readElementText().toDouble(&okStep);
    xmlReader->readNextStartElement();
    value = xmlReader->readElementText().toDouble(&okVal);
    xmlReader->readNext();

    if(!(okMax && okMin && okStep && okVal))
        throw ParseError;
}

bool DeviceParameter::operator==(DeviceParameter& two)
{
    if (name != two.name)
        return false;

    if (unit != two.unit)
        return false;

    if (max != two.max)
        return false;

    if (min != two.min)
        return false;

    if (value != two.value)
        return false;

    return true;
}
