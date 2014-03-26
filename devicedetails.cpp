#include "devicedetails.h"
#include "ui_devicedetails.h"

DeviceDetails::DeviceDetails(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeviceDetails)
{
    ui->setupUi(this);
}

DeviceDetails::~DeviceDetails()
{
    delete ui;
}

void DeviceDetails::sendMessage()
{
    QLCDNumber* lcd = this->findChild<QLCDNumber*>("address");
    Message msg;
    msg.address = lcd->value();

    QLineEdit* command = this->findChild<QLineEdit*>("command");
    QString commText = command->text();

    if(commText.length() == 0)
        return;

    msg.command = commText.at(0).toLatin1();
    msg.params = commText.right(commText.size() - 1);

    qint64 noOfBytes = AppState::GetCommPort()->write(msg);
    if(noOfBytes == -1)
        QMessageBox(QMessageBox::Critical,"Error", AppState::GetCommPort()->getPort()->errorString()).exec();
}

void DeviceDetails::chooseCommand()
{
    NOT_YET_READY
}

void DeviceDetails::sendParameters()
{
    NOT_YET_READY
}
