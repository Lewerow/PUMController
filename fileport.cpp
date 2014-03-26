#include "fileport.h"
#include <QFileDialog>

FilePort::FilePort(QString inputFilename, QString outputFilename) :
    PUMCommunication()
{
    commDevice = NULL;
    inputFile = NULL;
    deviceName = "File";

    setOutputCommFile(outputFilename);
    setInputCommFile(inputFilename);
    protocol = new PUMProtocol();
}

FilePort::~FilePort()
{
    if(commDevice != NULL)
    {
        delete commDevice;
        commDevice = NULL;
        delete inputFile;
        inputFile = NULL;
        localThread.exit(0);
    }

    delete protocol;
}

void FilePort::setInputCommFile(QString filename)
{
    if(inputFilename == filename)
        return;

    inputFilename = filename;
    if(inputFile != NULL)
    {
        inputFile->close();
        delete inputFile;
        inputFile = NULL;
    }

    inputFile = new QFile(filename);
}

void FilePort::setOutputCommFile(QString filename)
{
    if(outputFilename == filename)
        return;

    outputFilename = filename;

    if(commDevice != NULL)
    {
        commDevice->close();
        delete commDevice;
        commDevice = NULL;
    }

    commDevice = new QFile(filename);
}


void FilePort::open()
{
    if(commDevice == NULL)
        commDevice = new QFile(outputFilename);

    commDevice->open(QIODevice::WriteOnly);

    if(inputFile == NULL)
        inputFile = new QFile(inputFilename);

    inputFile->open(QIODevice::ReadOnly);
}

bool FilePort::isValid()
{
    if(commDevice == NULL || inputFile == NULL)
        return false;

    if(!(commDevice->isWritable() && inputFile->isReadable()))
        return false;

    return true;
}

Message FilePort::read()
{
    Message msg = protocol->unpack(inputFile->readLine());
    emit messageReceived(msg);
    logIt(msg);
    return msg;
}

void FilePort::close()
{
    dynamic_cast<QFile*>(commDevice)->flush();
    if(commDevice->isOpen())
        commDevice->close();

    if(inputFile->isOpen())
        inputFile->close();
}
