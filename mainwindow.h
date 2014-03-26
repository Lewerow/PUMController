#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "devicebox.h"
#include "communicationconfigure.h"
#include "consoleinterface.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    void connectActions();

private slots:
    void runConfigure();
    void runCommConsole();

};

#endif // MAINWINDOW_H
