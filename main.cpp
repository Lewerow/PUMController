#include "mainwindow.h"
#include "appstate.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    AppState app;
    app.Initialize();
    QApplication a(argc, argv);

    a.connect(&a, SIGNAL(aboutToQuit()), &app, SLOT(Cleanup()));
    MainWindow w;
    w.show();
    
    return a.exec();
}


