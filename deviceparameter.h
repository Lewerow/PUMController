#ifndef DEVICEPARAMETER_H
#define DEVICEPARAMETER_H

#include "globals.h"

class DeviceParameter
{
public:
    DeviceParameter();

    QString name;
    QString unit;

    double max;
    double min;
    double step;

    void writeToXML(QXmlStreamWriter* xmlWriter);
    void readFromXML(QXmlStreamReader* xmlReader);

    void setValue(double newVal)
    {value = (newVal > max) ? max : (newVal < min) ? min : newVal;}
    double getValue()
    {return value;}

    bool operator==(DeviceParameter& two);
    bool operator!=(DeviceParameter& two)
    {return !(*this==two);}

protected:
    double value;

};

#endif // DEVICEPARAMETER_H
