#ifndef DEVICEFRAME_H
#define DEVICEFRAME_H

#include <QFrame>

namespace Ui {
class DeviceFrame;
}

class DeviceFrame : public QFrame
{
    Q_OBJECT
    
public:
    explicit DeviceFrame(QWidget *parent = 0);
    ~DeviceFrame();
    
private:
    Ui::DeviceFrame *ui;
};

#endif // DEVICEFRAME_H
