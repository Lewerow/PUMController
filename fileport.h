#ifndef FILEPORT_H
#define FILEPORT_H

#include <QFile>
#include "pumcommunication.h"

class FilePort : public PUMCommunication
{
public:
    FilePort(QString inputFilename, QString outputFilename);
    virtual ~FilePort();

    virtual void close();
    virtual void open();
    virtual bool isValid();

    void setOutputCommFile(QString filename);
    void setInputCommFile(QString filename);

    QString getInputFilename()
        {return inputFilename;}
    QString getOutputFilename()
        {return outputFilename;}
protected:
    virtual void waitForData(){} // does nothing - if there is no data now, there will be no data
public slots:
    virtual Message read();

private:
    QString inputFilename;
    QString outputFilename;

    QFile* inputFile;


};

#endif // FILEPORT_H
