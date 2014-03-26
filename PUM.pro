#-------------------------------------------------
#
# Project created by QtCreator 2013-04-15T16:05:41
#
#-------------------------------------------------

QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PUM
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    communicationconfigure.cpp \
    pumcommunication.cpp \
    devicebox.cpp \
    device.cpp \
    consoleinterface.cpp \
    deviceparameter.cpp \
    fileport.cpp \
    pumprotocol.cpp \
    message.cpp \
    devicedetails.cpp \
    appstate.cpp \
    favouritecommands.cpp \
    rs232port.cpp \
    utilities.cpp \
    command.cpp

HEADERS  += mainwindow.h \
    message.h \
    communicationconfigure.h \
    pumcommunication.h \
    globals.h \
    devicebox.h \
    devicedetails.h \
    device.h \
    consoleinterface.h \
    deviceparameter.h \
    fileport.h \
    pumprotocol.h \
    appstate.h \
    favouritecommands.h \
    rs232port.h \
    command.h

FORMS    += mainwindow.ui \
    communicationconfigure.ui \
    devicebox.ui \
    devicedetails.ui \
    consoleinterface.ui \
    favouritecommands.ui
include(QextSerialPort1.2RC\src\qextserialport.pri)

OTHER_FILES += \
    protokol.txt \
    ../uwagi.txt \
