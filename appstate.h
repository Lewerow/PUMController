#ifndef APPSTATE_H
#define APPSTATE_H

#include "fileport.h"

#include <QObject>

class AppState : public QObject
{
    Q_OBJECT

public:
    AppState();
    virtual ~AppState();

    static PUMCommunication* GetCommPort()
        {return commPort;}
    static void SetCommPort(PUMCommunication* newCommPort);

    static void Initialize();
public slots:
    static void Cleanup();

private:
    static PUMCommunication* commPort;
};

#endif // APPSTATE_H
