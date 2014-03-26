#ifndef COMMUNICATIONCONFIGURE_H
#define COMMUNICATIONCONFIGURE_H

#include <QDialog>
#include "pumcommunication.h"
#include "fileport.h"
#include "appstate.h"

namespace Ui {
class CommunicationConfigure;
}

class CommunicationConfigure : public QDialog
{
    Q_OBJECT
    
public:
    explicit CommunicationConfigure(QWidget *parent = 0);
    ~CommunicationConfigure();

signals:
    void communicationDeviceChanged();

private:
    Ui::CommunicationConfigure *ui;

    void configureFileUI();
    void configureRSUI();

private slots:
    void testConnection();
    void setActivePort();
    void closeActivePort();

    // for fileport
    void getInputFile();
    void getOutputFile();
    void confirmFile();

    // for rs232 port
    void confirmRS();
    void checkTimeoutEnabled();


};

#endif // COMMUNICATIONCONFIGURE_H
