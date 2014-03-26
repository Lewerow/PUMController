#include "favouritecommands.h"
#include "ui_favouritecommands.h"

#include <QLabel>
#include <QLineEdit>
#include "appstate.h"

extern QMap<QString, Command> FavouriteCommands::commandSet;

FavouriteCommands::FavouriteCommands(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FavouriteCommands)
{
    ui->setupUi(this);
    if(commandSet.size()==0)
        loadCommands();

    displayCommands();
}

FavouriteCommands::~FavouriteCommands()
{
    delete ui;
}

void FavouriteCommands::saveCommands(QString filepath)
{
    synchronizeCommandsWithTable();

    QFile xmlFile(filepath);
    xmlFile.open(QIODevice::WriteOnly);

    if(!xmlFile.isOpen())
    {
        QMessageBox(QMessageBox::Warning, QString("Błąd zapisu"), QString("Nie udało się otworzyć pliku")).exec();
        return;
    }

    QXmlStreamWriter xmlWriter(&xmlFile);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("commands");
    for(QMap<QString, Command>::iterator i = commandSet.begin(); i != commandSet.end(); i++)
        i->writeToXML(&xmlWriter);

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    xmlFile.flush();
    xmlFile.close();
}

void FavouriteCommands::loadCommands(QString filepath)
{
    QFile xmlFile(filepath);
    xmlFile.open(QIODevice::ReadOnly);

    if(!xmlFile.isOpen())
    {
        QMessageBox(QMessageBox::Warning, QString("Błąd odczytu"), QString("Nie udało się wczytać komend")).exec();
        return;
    }

    QXmlStreamReader xmlReader(&xmlFile);

    if(xmlReader.isStartDocument())
        xmlReader.readNextStartElement();

    xmlReader.readNextStartElement();

    if(!xmlReader.isEndDocument())
    {
        do
        {
            Command newCommand;
            newCommand.readFromXML(&xmlReader);
            commandSet.insert(newCommand.getName(), newCommand);
        }while(!xmlReader.atEnd() && xmlReader.name() != QString("commands"));
    }

    if(commandSet.contains(QString("")))
        commandSet.remove(QString(""));


    xmlFile.close();
}

void FavouriteCommands::displayCommands()
{
    QTableWidget* commandTable = findChild<QTableWidget*>("commandTable");
    commandTable->setColumnWidth(0, 100);
    commandTable->setColumnWidth(1,170);
    commandTable->setColumnWidth(2,70);
    commandTable->horizontalHeader()->setVisible(true);

    int num = 0;
    commandTable->setRowCount(commandSet.size()+1);
    for(QMap<QString, Command>::iterator i = commandSet.begin(); i!=commandSet.end();i++)
    {
        QLineEdit* nameEdit = new QLineEdit(i.key());
        QLineEdit* msgEdit = new QLineEdit(i.value().getMsg().report());
        QPushButton* sendButton = new QPushButton(QString("Wyślij"));
        connect(sendButton,SIGNAL(clicked()),this,SLOT(prepareAndSend()));

        sendButton->setObjectName(QString("__sendButton_row_") + QString::number(num));
        commandTable->setCellWidget(num,0,nameEdit);
        commandTable->setCellWidget(num,1,msgEdit);
        commandTable->setCellWidget(num,2,sendButton);
        commandTable->setRowHeight(num, 25);
        num++;

    }

    QLineEdit* nameEdit = new QLineEdit;
    QLineEdit* msgEdit = new QLineEdit;
    QPushButton* addButton = new QPushButton(QString("Dodaj"));
    connect(addButton,SIGNAL(clicked()),this,SLOT(addCommand()));

    commandTable->setCellWidget(num,0,nameEdit);
    commandTable->setCellWidget(num,1,msgEdit);
    commandTable->setCellWidget(num,2,addButton);
    commandTable->setRowHeight(num, 25);
}

void FavouriteCommands::addCommand()
{
    QTableWidget* commandTable = findChild<QTableWidget*>("commandTable");
    QLineEdit* newName = static_cast<QLineEdit*>(commandTable->cellWidget(commandSet.size(), 0));
    QLineEdit* newMsg = static_cast<QLineEdit*>(commandTable->cellWidget(commandSet.size(), 1));
    Command newCommand;
    newCommand.setName(newName->text());
    newCommand.setMsg(Message(newMsg->text()));
    commandSet.insert(newName->text(), newCommand);

    commandTable->setRowCount(commandSet.size()+1);
    commandTable->cellWidget(commandSet.size()-1,2)->disconnect(this);
    QPushButton* sendButton = new QPushButton(QString("Wyślij"));
    sendButton->setObjectName(QString("__sendButton_row_") + QString::number(commandSet.size()-1));
    commandTable->cellWidget(commandSet.size()-1, 2)->deleteLater();
    commandTable->setCellWidget(commandSet.size()-1, 2, sendButton);

    connect(sendButton, SIGNAL(clicked()), this, SLOT(prepareAndSend()));

    QLineEdit* nameEdit = new QLineEdit;
    QLineEdit* msgEdit = new QLineEdit;
    QPushButton* addButton = new QPushButton(QString("Dodaj"));
    connect(addButton,SIGNAL(clicked()),this,SLOT(addCommand()));

    commandTable->setCellWidget(commandSet.size(),0,nameEdit);
    commandTable->setCellWidget(commandSet.size(),1,msgEdit);
    commandTable->setCellWidget(commandSet.size(),2,addButton);
    commandTable->setRowHeight(commandSet.size(), 25);
}

void FavouriteCommands::synchronizeCommandsWithTable()
{
    QTableWidget* commandTable = findChild<QTableWidget*>("commandTable");
    QMap<QString, bool> areThereStill;

    for(QMap<QString, Command>::iterator i = commandSet.begin(); i != commandSet.end(); i++)
        areThereStill.insert(i.key(), false);

    for(int i = 0; i < commandTable->rowCount(); i++)
    {
        QLineEdit* nameLabel = static_cast<QLineEdit*>(commandTable->cellWidget(i,0));
        QLineEdit* msgTextLabel = static_cast<QLineEdit*>(commandTable->cellWidget(i,1));

        if(commandSet.contains(nameLabel->text()))
        {
            areThereStill[nameLabel->text()] = true;

            if(commandSet[nameLabel->text()].getMsg().report() != msgTextLabel->text())
                commandSet[nameLabel->text()].setMsg(Message(msgTextLabel->text()));
        }
        else
        {
            Command nComm;
            nComm.setName(nameLabel->text());
            nComm.setMsg(Message(msgTextLabel->text()));
            commandSet.insert(nameLabel->text(), nComm);
        }
    }

    for(QMap<QString, bool>::iterator i = areThereStill.begin(); i != areThereStill.end(); i++)
    {
        if(i.value() == false)
            commandSet.remove(i.key());
    }
}

void FavouriteCommands::prepareAndSend()
{
    QTableWidget* commandTable = findChild<QTableWidget*>("commandTable");
    QPushButton* activeButton = static_cast<QPushButton*>(QWidget::focusWidget());
    qDebug(activeButton->objectName().toLocal8Bit());
    int startOfNumber = activeButton->objectName().lastIndexOf("_");
    qDebug(activeButton->objectName().right(activeButton->objectName().size() - startOfNumber-1).toLocal8Bit());
    int rowNum = activeButton->objectName().right(activeButton->objectName().size() - startOfNumber-1).toInt();
    QLineEdit* commandName = static_cast<QLineEdit*>(commandTable->cellWidget(rowNum,0));
    qDebug(commandName->text().toLocal8Bit());

    QLineEdit* entireMsg = static_cast<QLineEdit*>(commandTable->cellWidget(rowNum,1));
    if(entireMsg->text().size() < 2)
    {
        QMessageBox(QMessageBox::Warning, "Za krótka komenda", "Wiadomość musi mieć co najmniej dwa znaki - adres i komendę").exec();
        return;
    }

    qint64 noOfBytes = AppState::GetCommPort()->write(Message(entireMsg->text()));
    if(noOfBytes == -1)
        QMessageBox(QMessageBox::Critical,"Error", AppState::GetCommPort()->getPort()->errorString()).exec();
}
