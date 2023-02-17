#include "robotcontrol.h"
#include "ui_robotcontrol.h"

RobotControl::RobotControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RobotControl)
{
    ui->setupUi(this);

    m_connectui = new Connect(this);
    m_connectui->hide();

    connect(m_connectui, &Connect::Connected, this, &RobotControl::Connected);
    connect(m_connectui, &Connect::HasData, this, &RobotControl::GetData);

    m_term = new DataTerminal(this);
    m_term->show();

    connect(m_term, &DataTerminal::MustSendLine, this, &RobotControl::SendCmd);
    connect(ui->pTerm, &QPushButton::clicked, m_term, &DataTerminal::show);

    connect(ui->pStop, &QPushButton::clicked, this, &RobotControl::StopBot);

    ui->pSend->setEnabled(false);
    ui->pStop->setEnabled(false);
}

RobotControl::~RobotControl()
{
    delete ui;
}

void RobotControl::keyPressEvent(QKeyEvent* e) {
}

void RobotControl::ConnectToRobot() {
    m_connectui->Reset();
    m_connectui->show();
}

void RobotControl::Connected() {
    ui->pSend->setEnabled(true);
    ui->pConnect->setEnabled(false);
    ui->pStop->setEnabled(true);

    m_connectui->hide();

    m_socket = m_connectui->GetHandle();

    CmdGetInfo();
}

void RobotControl::SendData() {
    std::string query;
    query += "setPwm -l ";
    query += std::to_string(ui->spLMot->value());

    query += " -r ";
    query+= std::to_string(ui->spRMot->value());

    query += "\n";

    SendCommand(query);
}

void RobotControl::LaunchMTest() {
    std::string query;
    query = "autotest pwmL pwmR \n";

    SendCommand(query);
}

void RobotControl::GetData() {
    QString newData = m_connectui->RetreiveData();
    m_term->AppendData(newData);
}

void RobotControl::CmdGetInfo() {
    SendCommand("getSoftwareInfos \n");
}

void RobotControl::SendCmd(QString data) {
    std::string query = data.toStdString();
    SendCommand(query);
}

void RobotControl::SendCommand(std::string cmd) {
    if(m_socket) {
        m_socket->write(cmd.c_str());
    }

    m_term->AppendData("> " + QString::fromStdString(cmd));
}

void RobotControl::StopBot() {
    SendCommand("setPwm -l 0 -r 0 \n");

    ui->spLMot->setValue(0);
    ui->spRMot->setValue(0);
}
