#ifndef DEVICE_H
#define DEVICE_H

using namespace std;
#include "deviceparameter.h"

class Device
{
public:
    Device();

    virtual void readFromXML(QXmlStreamReader* xmlReader);
    virtual void writeToXML(QXmlStreamWriter* xmlWriter);

protected:
    QString name;
    DeviceType type;
    DeviceClass className;
    DeviceAddress address;

    vector<DeviceParameter> params;
};

#endif // DEVICE_H
