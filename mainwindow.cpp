#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->connectActions();
}

void MainWindow::connectActions()
{
    QAction* closeMe = findChild<QAction*>("aClose");
    connect(closeMe, SIGNAL(triggered()), this, SLOT(close()));
    QAction* configure = findChild<QAction*>("aConfigure");
    connect(configure, SIGNAL(triggered()), this, SLOT(runConfigure()));
    QAction* console = findChild<QAction*>("aConsole_2");
    connect(console, SIGNAL(triggered()), this, SLOT(runCommConsole()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::runConfigure()
{
    CommunicationConfigure* commWindow = new CommunicationConfigure;
    commWindow->exec();
}

void MainWindow::runCommConsole()
{
    ConsoleInterface* consWindow = new ConsoleInterface;
    consWindow->exec();
}

