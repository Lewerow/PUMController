#include "consoleinterface.h"
#include "ui_consoleinterface.h"
#include "communicationconfigure.h"
#include "qextserialport.h"
#include "favouritecommands.h"

#include <QLineEdit>

extern QString baudRateToText(BaudRateType bRate);

ConsoleInterface::ConsoleInterface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConsoleInterface)
{
    ui->setupUi(this);
    sentData = NULL;
    receivedData = NULL;
    remakeCommunication();
}

ConsoleInterface::~ConsoleInterface()
{
    delete sentData;
    delete receivedData;
    delete ui;
}

void ConsoleInterface::sendMessage()
{
    if(AppState::GetCommPort() == NULL)
    {
        QMessageBox(QMessageBox::Critical, "Brak portu", "Port komunikacyjny nie został jeszcze zdefiniowany").exec();
        return;
    }

    Message msg;
    QLineEdit* command = findChild<QLineEdit*>("offlineCommand");
    QString commText = command->text();

    if(commText.length() < 2)
    {
        QMessageBox(QMessageBox::Warning, "Za krótka komenda", "Wiadomość musi mieć co najmniej dwa znaki - adres i komendę").exec();
        return;
    }
    command->clear();

    msg.loadFromQString(commText);

    qint64 noOfBytes = AppState::GetCommPort()->write(msg);
    if(noOfBytes == -1)
        QMessageBox(QMessageBox::Critical,"Error", AppState::GetCommPort()->getPort()->errorString()).exec();
}

void ConsoleInterface::chooseCommand()
{
    if(AppState::GetCommPort() == NULL)
    {
        QMessageBox(QMessageBox::Critical, "Brak portu", "Port komunikacyjny nie został jeszcze zdefiniowany").exec();
        return;
    }

    FavouriteCommands comm;
    comm.exec();
}

void ConsoleInterface::configureCommunication()
{
    CommunicationConfigure* configureNew = new CommunicationConfigure;
    connect(configureNew,SIGNAL(communicationDeviceChanged()),this,SLOT(remakeCommunication()));
    configureNew->exec();
    delete configureNew;
}

void ConsoleInterface::remakeCommunication()
{
    QLabel* connectionData = findChild<QLabel*>("connectionData");
    QListView* receivedDataView = findChild<QListView*>("receivedView");
    QListView* sentDataView = findChild<QListView*>("sentView");
    PUMCommunication* commPort = AppState::GetCommPort();

    if(sentData == NULL)
    {
        sentData = new QStringListModel;
        sentDataView->setModel(sentData);
    }
    if(receivedData == NULL)
    {
        receivedData = new QStringListModel;
        receivedDataView->setModel(receivedData);
    }

    if(commPort == NULL)
    {
        connectionData->setText("Nie wybrano żadnego urządzenia");
        sentData->setStringList(sentData->stringList()<<"Brak urządzenia");
        receivedData->setStringList(receivedData->stringList()<<"Brak urządzenia");
        return;
    }

    else
    {
        connect(commPort,SIGNAL(messageSent(Message)),this,SLOT(recordSentMessage(Message)));
        connect(commPort,SIGNAL(messageReceived(Message)), this,SLOT(recordReceivedMessage(Message)));

        if(commPort->getDeviceName() == "RS232")
        {
            QString portParams;
            portParams.append("Port: RS232\n");
            QextSerialPort* currentRS = static_cast<QextSerialPort*>(commPort->getPort());

            QString sBaudRate = baudRateToText(currentRS->baudRate());

            portParams.append("Nazwa portu: " + currentRS->portName() + "\n");
            portParams.append("Prędkość: " + sBaudRate + "bps \n");

            connectionData->setText(portParams);
            sentData->setStringList(sentData->stringList()<<"Wysyłanie przez port RS232: " + currentRS->portName());
            receivedData->setStringList(receivedData->stringList()<<"Odczyt z portu RS232: " + currentRS->portName());
        }

        else if(commPort->getDeviceName() == "File")
        {
            QString portParams;
            portParams.append("Port: Plik\n");
            FilePort* fCommPort = static_cast<FilePort*>(commPort);
            portParams.append("Plik wejściowy: " + fCommPort->getInputFilename() + "\n");
            portParams.append("Plik wyjściowy: " + fCommPort->getOutputFilename() + "\n");

            connectionData->setText(portParams);
            sentData->setStringList(sentData->stringList()<<"Wysyłanie do pliku: "+fCommPort->getOutputFilename());
            receivedData->setStringList(receivedData->stringList()<<"Odczyt z pliku: "+fCommPort->getInputFilename());
        }

        else
        {
            connectionData->setText("Nieznany rodzaj portu");
            sentData->setStringList(sentData->stringList()<<"Nieznany port");
            receivedData->setStringList(receivedData->stringList()<<"Nieznany port");
        }
    }
}

void ConsoleInterface::recordSentMessage(Message sent)
{
    QListView* sentDataView = findChild<QListView*>("sentView");
    sentData->setStringList(sentData->stringList()<<QTime::currentTime().toString() + "-> " + sent.report());
    sentDataView->scrollToBottom();

}

void ConsoleInterface::recordReceivedMessage(Message received)
{
    QListView* receivedDataView = findChild<QListView*>("receivedView");
    receivedData->setStringList(receivedData->stringList()<<QTime::currentTime().toString() + "-> " + received.report());
    receivedDataView->scrollToBottom();
}
