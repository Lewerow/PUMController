#include "deviceframe.h"
#include "ui_deviceframe.h"

DeviceFrame::DeviceFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DeviceFrame)
{
    ui->setupUi(this);
}

DeviceFrame::~DeviceFrame()
{
    delete ui;
}
