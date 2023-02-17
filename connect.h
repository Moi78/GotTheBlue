#ifndef CONNECT_H
#define CONNECT_H

#include <QWidget>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothSocket>

#include <QList>

namespace Ui {
class Connect;
}

class Connect : public QWidget
{
    Q_OBJECT

public:
    explicit Connect(QWidget *parent = nullptr);
    ~Connect();

    QBluetoothSocket* GetHandle();
    QString RetreiveData();

    void Reset();

public slots:
    void FoundDevice(const QBluetoothDeviceInfo& dev);
    void ConnectBT();

    void Success();
    void LostConnection();

    void CanRead();

signals:
    void Connected();
    void Disconnected();
    void HasData();

private:
    Ui::Connect *ui;

    QBluetoothDeviceDiscoveryAgent* m_scanner;
    QList<QBluetoothDeviceInfo> m_devices;

    QByteArray m_buffer;

    QBluetoothSocket* m_socket;
};

#endif // CONNECT_H
