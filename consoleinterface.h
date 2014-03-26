#ifndef CONSOLEINTERFACE_H
#define CONSOLEINTERFACE_H

#include <QDialog>
#include <QStringListModel>
#include "pumcommunication.h"
#include "appstate.h"

namespace Ui {
class ConsoleInterface;
}

class ConsoleInterface : public QDialog
{
    Q_OBJECT
    
public:
    explicit ConsoleInterface(QWidget *parent = 0);
    ~ConsoleInterface();
    
private:
    Ui::ConsoleInterface *ui;

    QStringListModel* sentData;
    QStringListModel* receivedData;

private slots:
    void sendMessage();
    void chooseCommand();
    void configureCommunication();
    void remakeCommunication();

    void recordSentMessage(Message sent);
    void recordReceivedMessage(Message received);
};

#endif // CONSOLEINTERFACE_H
