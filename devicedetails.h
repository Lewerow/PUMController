#ifndef DEVICEDETAILS_H
#define DEVICEDETAILS_H

#include <QDialog>

#include <QLineEdit>
#include <QLCDNumber>

#include "device.h"
#include "appstate.h"

namespace Ui {
class DeviceDetails;
}

class DeviceDetails : public QDialog
{
    Q_OBJECT
    
public:
    explicit DeviceDetails(QWidget *parent = 0);
    ~DeviceDetails();
    
private:
    Device* device;
    Ui::DeviceDetails *ui;

private slots:
    void sendMessage();
    void chooseCommand();
    void sendParameters();
};

#endif // DEVICEDETAILS_H
