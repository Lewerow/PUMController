#ifndef GLOBALS_H
#define GLOBALS_H


// standard library
#include <vector>


// Qt
#include <QtCore>
#include <QString>
#include <QByteArray>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

#include <QMessageBox>

// constants
const unsigned char START_SYMBOL = 255; // 0xFF
const unsigned char END_SYMBOL = 10; // CR

const QString END_OF_LINE = "\10\13";

// typedefs
typedef unsigned char CommunicationType;
typedef unsigned char DeviceAddress;
typedef unsigned char CommandType;

// enums
enum DeviceType{
    Engine = 1000,
    Sensor = 2000,
    Relay = 3000,
    Other = 4000
};

enum DeviceClass{
    DCMotor = 1,
    Servomotor = 2,
    OtherMotor = 999,
    Encoder = 1000,
    OtherSensor = 1999,
    OtherDevice = 10000
};

enum ErrorCode {
    CommunicationError = 1000,
    FileNotFound = 1100,
    ParseError = 1200,
    InvalidPackage = 1300,
    NoCommunicationPort = 1400
};

// definitions
#ifndef NULL
    #define NULL 0
#endif // NULL

#define NOT_YET_READY QMessageBox(QMessageBox::Warning, "Jeszcze nie opracowane", "Praca w toku").exec();

#endif // GLOBALS_H
