#include "devicebox.h"
#include "ui_devicebox.h"

DeviceBox::DeviceBox(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::DeviceBox)
{
    ui->setupUi(this);
}

DeviceBox::~DeviceBox()
{
    delete ui;
}

void DeviceBox::openDetails()
{
    DeviceDetails* newDetails = new DeviceDetails;
    newDetails->exec();

    delete newDetails;
}

void DeviceBox::sendChanges()
{
    NOT_YET_READY
}
