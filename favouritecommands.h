#ifndef FAVOURITECOMMANDS_H
#define FAVOURITECOMMANDS_H

#include <QDialog>
#include "command.h"
#include <QMap>

namespace Ui {
class FavouriteCommands;
}

class FavouriteCommands : public QDialog
{
    Q_OBJECT
    
public:
    explicit FavouriteCommands(QWidget *parent = 0);
    ~FavouriteCommands();
    
private:
    Ui::FavouriteCommands *ui;
    static QMap<QString, Command> commandSet;

    void displayCommands();
    void synchronizeCommandsWithTable();
private slots:
    void loadCommands(QString filepath = QString("data/favourite_commands.xml"));
    void saveCommands(QString filepath = QString("data/favourite_commands.xml"));
    void addCommand();
    void prepareAndSend();
};

#endif // FAVOURITECOMMANDS_H
