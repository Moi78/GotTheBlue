#include "connect.h"
#include "ui_connect.h"

Connect::Connect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Connect)
{
    ui->setupUi(this);

    m_scanner = new QBluetoothDeviceDiscoveryAgent(this);
    connect(m_scanner, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, &Connect::FoundDevice);

    m_scanner->start();

    m_socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    connect(m_socket, &QBluetoothSocket::connected, this, &Connect::Success);
    connect(m_socket, &QBluetoothSocket::disconnected, this, &Connect::LostConnection);
    connect(m_socket, &QBluetoothSocket::readyRead, this, &Connect::CanRead);

    connect(ui->bConnect, &QPushButton::pressed, this, &Connect::ConnectBT);

    QWidget::setWindowFlags(Qt::Window);
}

Connect::~Connect()
{
    delete ui;

    m_socket->close();
}

void Connect::FoundDevice(const QBluetoothDeviceInfo& dev) {
    ui->deviceList->addItem(dev.name());

    m_devices.append(dev);
}

void Connect::ConnectBT() {
    m_scanner->stop();
    ui->deviceList->setEnabled(false);

    QBluetoothDeviceInfo dev;
    for(auto& d : m_devices) {
        if(d.name() == ui->deviceList->currentText()) {
            dev = d;
            break;
        }
    }

    qDebug() << "Connecting to " << dev.name() << "\n";

    QBluetoothServiceInfo srv = QBluetoothServiceInfo();
    srv.setDevice(dev);
    srv.setServiceUuid(QBluetoothUuid::ServiceClassUuid::SerialPort);

    m_socket->connectToService(srv);
}

QBluetoothSocket* Connect::GetHandle() {
    return m_socket;
}

void Connect::Success() {
    emit Connected();
}

void Connect::Reset() {
    m_devices.clear();
    ui->deviceList->clear();

    m_scanner->stop();
    m_scanner->start();

    ui->deviceList->setEnabled(true);
}

void Connect::LostConnection() {
    emit Disconnected();
}

void Connect::CanRead() {
    while(m_socket->canReadLine()) {
        QByteArray line = m_socket->readLine().trimmed() + '\n';
        m_buffer += line;
    }

    if(m_buffer != "") {
        emit HasData();
    }
}

QString Connect::RetreiveData() {
    QString buff_copy(m_buffer);
    m_buffer.clear();

    return buff_copy;
}

