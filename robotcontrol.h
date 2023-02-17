#ifndef ROBOTCONTROL_H
#define ROBOTCONTROL_H

#include <QWidget>
#include <QKeyEvent>
#include <QShortcut>

#include "connect.h"
#include "dataterminal.h"

#include <string>

namespace Ui {
class RobotControl;
}

class RobotControl : public QWidget
{
    Q_OBJECT

public:
    explicit RobotControl(QWidget *parent = nullptr);
    ~RobotControl();

    void CmdGetInfo();
    void SendCommand(std::string cmd);

    virtual void keyPressEvent(QKeyEvent* e) override;

public slots:
    void ConnectToRobot();
    void Connected();

    void SendData();
    void LaunchMTest();

    void GetData();
    void SendCmd(QString data);

    void StopBot();

private:
    Ui::RobotControl *ui;

    Connect* m_connectui;
    DataTerminal* m_term;

    QBluetoothSocket* m_socket;
};

#endif // ROBOTCONTROL_H
