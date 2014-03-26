#include "appstate.h"

extern PUMCommunication* AppState::commPort;

AppState::AppState()
{
}

AppState::~AppState()
{
}

void AppState::SetCommPort(PUMCommunication* newCommPort)
{
    if(commPort != NULL)
        delete commPort;

    commPort = newCommPort;
}

void AppState::Initialize()
{
    commPort = NULL;
    qRegisterMetaType<Message>("Message");
}

void AppState::Cleanup()
{
    if(commPort != NULL)
    {
        commPort->close();
        delete commPort;
        commPort = NULL;
    }
}
