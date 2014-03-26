#ifndef DEVICEBOX_H
#define DEVICEBOX_H

#include <QGroupBox>
#include "devicedetails.h"

namespace Ui {
class DeviceBox;
}

class DeviceBox : public QGroupBox
{
    Q_OBJECT
    
public:
    explicit DeviceBox(QWidget *parent = 0);
    ~DeviceBox();
    
private:
    Ui::DeviceBox *ui;
    Device* device;

private slots:
    void openDetails();
    void sendChanges();
};

#endif // DEVICEBOX_H
