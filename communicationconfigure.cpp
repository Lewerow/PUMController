#include "communicationconfigure.h"
#include "ui_communicationconfigure.h"
#include "rs232port.h"

#include <QFileDialog>
#include <qextserialport.h>
#include "QextSerialPort1.2RC/src/qextserialport.h"
#include "QextSerialPort1.2RC/src/qextserialport_p.h"
#include "QextSerialPort1.2RC/src/qextserialport_global.h"
#include "QextSerialPort1.2RC/src/qextserialenumerator.h"

extern QString baudRateToText(BaudRateType bRate);
extern QString parityToText(ParityType bRate);
extern QString stopBitsToText(StopBitsType bRate);
extern QString dataBitsToText(DataBitsType bRate);


CommunicationConfigure::CommunicationConfigure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CommunicationConfigure)
{
    ui->setupUi(this);
    configureRSUI();
    QTabWidget* tabs = findChild<QTabWidget*>("configurations");
    tabs->tabBar()->hide();

    setActivePort();

    QComboBox* queryModeBox = findChild<QComboBox*>("rsQueryMode");
    QComboBox* timeoutBox = findChild<QComboBox*>("rsTimeout");
    QLabel* queryLabel = findChild<QLabel*>("queryLabel");
    QLabel* timeoutLabel = findChild<QLabel*>("timeoutLabel");

    queryModeBox->setVisible(false);
    timeoutBox->setVisible(false);
    queryLabel->setVisible(false);
    timeoutLabel->setVisible(false);

}

CommunicationConfigure::~CommunicationConfigure()
{
    delete ui;
}

void CommunicationConfigure::configureFileUI()
{
    NOT_YET_READY
}

void CommunicationConfigure::configureRSUI()
{
    QComboBox* portBox = findChild<QComboBox*>("rsPort");
    foreach (QextPortInfo info, QextSerialEnumerator::getPorts())
        portBox->addItem(info.portName);

    //make sure user can input their own port name!
    portBox->setEditable(true);

    QComboBox* baudRateBox = findChild<QComboBox*>("rsBaudRate");
    baudRateBox->addItem("1200", BAUD1200);
    baudRateBox->addItem("2400", BAUD2400);
    baudRateBox->addItem("4800", BAUD4800);
    baudRateBox->addItem("9600", BAUD9600);
    baudRateBox->addItem("19200", BAUD19200);
    baudRateBox->addItem("38400", BAUD38400);
    baudRateBox->addItem("57600", BAUD57600);
    baudRateBox->addItem("115200", BAUD115200);
    baudRateBox->setCurrentIndex(3);

    QComboBox* parityBox = findChild<QComboBox*>("rsParity");
    parityBox->addItem("NONE", PAR_NONE);
    parityBox->addItem("ODD", PAR_ODD);
    parityBox->addItem("EVEN", PAR_EVEN);

    QComboBox* dataBitsBox = findChild<QComboBox*>("rsDataBits");
    dataBitsBox->addItem("5", DATA_5);
    dataBitsBox->addItem("6", DATA_6);
    dataBitsBox->addItem("7", DATA_7);
    dataBitsBox->addItem("8", DATA_8);
    dataBitsBox->setCurrentIndex(3);

    QComboBox* stopBitsBox = findChild<QComboBox*>("rsStopBits");
    stopBitsBox->addItem("1", STOP_1);
    stopBitsBox->addItem("2", STOP_2);
    stopBitsBox->setCurrentIndex(1);

    QComboBox* queryModeBox = findChild<QComboBox*>("rsQueryMode");
    queryModeBox->addItem("Polling", QextSerialPort::Polling);
    queryModeBox->addItem("EventDriven", QextSerialPort::EventDriven);
    queryModeBox->setCurrentIndex(1);
}

void CommunicationConfigure::confirmRS()
{
    QComboBox* portBox = findChild<QComboBox*>("rsPort");
    QComboBox* baudRateBox = findChild<QComboBox*>("rsBaudRate");
    QComboBox* parityBox = findChild<QComboBox*>("rsParity");
    QComboBox* dataBitsBox = findChild<QComboBox*>("rsDataBits");
    QComboBox* stopBitsBox = findChild<QComboBox*>("rsStopBits");
//    QComboBox* queryModeBox = findChild<QComboBox*>("rsQueryMode");
//    QComboBox* timeoutBox = findChild<QComboBox*>("rsTimeout");

    QextSerialPort* port = new QextSerialPort(portBox->currentText());
    port->setBaudRate((BaudRateType)baudRateBox->currentText().toInt());
    port->setParity((ParityType)parityBox->currentText().toInt());
    port->setDataBits((DataBitsType)dataBitsBox->currentText().toInt());
    port->setStopBits((StopBitsType)stopBitsBox->currentText().toInt());
    /*port->setQueryMode((QextSerialPort::QueryMode)queryModeBox->currentIndex());

    if(port->queryMode() == QextSerialPort::Polling)
        port->setTimeout(timeoutBox->currentText().toInt());
    */

    try
    {
        RS232Port* newRS = new RS232Port(port);
        newRS->open();

        if(newRS->isValid())
        {
            AppState::SetCommPort(newRS);
            QMessageBox(QMessageBox::Information, "Port otwarty", "Port RS232 został otwarty poprawnie").exec();
            emit communicationDeviceChanged();
        }

        else
        {
            delete newRS;
            QMessageBox(QMessageBox::Critical, "Nie udało się otworzyć portu", "Nie udało się otworzyć wybranego portu RS232").exec();
        }
    }
    catch(...)
    {
        QMessageBox(QMessageBox::Critical, "Błąd", "Nieznany błąd").exec();
    }
}

void CommunicationConfigure::checkTimeoutEnabled()
{
    /*

    QComboBox* timeoutBox = findChild<QComboBox*>("rsTimeout");
    QComboBox* queryModeBox = findChild<QComboBox*>("rsQueryMode");

    if((QextSerialPort::QueryMode)queryModeBox->currentText().toInt() == QextSerialPort::Polling)
        timeoutBox->setEnabled(false);

    else
        timeoutBox->setEnabled(true);

    */
}


void CommunicationConfigure::testConnection()
{
    if(AppState::GetCommPort() != NULL && AppState::GetCommPort()->isValid())
        QMessageBox(QMessageBox::Information, "Poprawny stan portu","Port komunikacyjny jest dostępny. Typ portu: "+AppState::GetCommPort()->getDeviceName()).exec();
    else
        QMessageBox(QMessageBox::Warning, "Brak otwartego portu","Port komunikacyjny nie jest dostępny. Do komunikacji konieczne jest otwarcie nowego portu").exec();

}

void CommunicationConfigure::setActivePort()
{
    PUMCommunication* commPort = AppState::GetCommPort();

    if(commPort == NULL)
        return;

    if(commPort->getDeviceName() == "File")
    {
        QTabWidget* tabs = findChild<QTabWidget*>("configurations");
        tabs->tabBar()->setCurrentIndex(1);
        QLineEdit* outputFilename = findChild<QLineEdit*>("outputPath");
        QLineEdit* inputFilename = findChild<QLineEdit*>("inputPath");

        FilePort* fPort = static_cast<FilePort*>(commPort);

        outputFilename->setText(fPort->getOutputFilename());
        inputFilename->setText(fPort->getInputFilename());

        return;
    }

    if(commPort->getDeviceName() == "RS232")
    {

        QextSerialPort* rsPort = static_cast<QextSerialPort*>(commPort->getPort());
        QTabWidget* tabs = findChild<QTabWidget*>("configurations");
        tabs->tabBar()->setCurrentIndex(0);
        QComboBox* portBox = findChild<QComboBox*>("rsPort");
        portBox->setEditText(rsPort->portName());

        QComboBox* baudRateBox = findChild<QComboBox*>("rsBaudRate");
        baudRateBox->setEditText(baudRateToText(rsPort->baudRate()));

        QComboBox* parityBox = findChild<QComboBox*>("rsParity");
        parityBox->setEditText(parityToText(rsPort->parity()));

        QComboBox* dataBitsBox = findChild<QComboBox*>("rsDataBits");
        dataBitsBox->setEditText(dataBitsToText(rsPort->dataBits()));

        QComboBox* stopBitsBox = findChild<QComboBox*>("rsStopBits");
        stopBitsBox->setEditText(stopBitsToText(rsPort->stopBits()));

        return;
    }

}

void CommunicationConfigure::closeActivePort()
{
    AppState::GetCommPort()->close();
    QMessageBox(QMessageBox::Information, QString("Zamknięty port"), QString("Zamknięto dotychczasowy port komunikacyjny")).exec();
}

void CommunicationConfigure::getInputFile()
{
    QString path = QFileDialog::getOpenFileName(0,"Wybierz plik wejściowy");

    if(path != QString())
    {
        QLineEdit* inputFilename = findChild<QLineEdit*>("inputPath");
        inputFilename->setText(path);
    }
}

void CommunicationConfigure::getOutputFile()
{
    QString path = QFileDialog::getSaveFileName(0,"Wybierz plik wyjściowy");

    if(path != QString())
    {
        QLineEdit* outputFilename = findChild<QLineEdit*>("outputPath");
        outputFilename->setText(path);
    }
}

void CommunicationConfigure::confirmFile()
{
    try
    {
        QString inputFilename = findChild<QLineEdit*>("inputPath")->text();
        QString outputFilename = findChild<QLineEdit*>("outputPath")->text();
        FilePort* newPort = new FilePort(inputFilename, outputFilename);
        newPort->open();

        if(newPort->isValid())
        {
            AppState::SetCommPort(newPort);
            QMessageBox(QMessageBox::Information, "Port otwarty", "Port został otwarty poprawnie").exec();
            emit communicationDeviceChanged();
        }
        else
        {
            delete newPort;
            QMessageBox(QMessageBox::Critical, "Nie udało się otworzyć portu", "Nie udało się otworzyć portu do wybranych plików").exec();
        }
    }

    catch(ErrorCode er)
    {
        QMessageBox(QMessageBox::Critical, "Błąd odczytu pliku", "Nie znaleziono danego pliku").exec();
    }

    catch(...)
    {
        QMessageBox(QMessageBox::Critical, "Błąd", "Nieznany błąd").exec();
    }
}
