#include "dataterminal.h"
#include "ui_dataterminal.h"

DataTerminal::DataTerminal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataTerminal)
{
    ui->setupUi(this);

    connect(ui->btnSend, &QPushButton::clicked, this, &DataTerminal::WantToSend);
    connect(ui->commandLine, &QLineEdit::returnPressed, this, &DataTerminal::WantToSend);

    QWidget::setWindowFlags(Qt::Window);
}

DataTerminal::~DataTerminal()
{
    delete ui;
}

void DataTerminal::AppendData(QString data) {
    ui->textData->insertPlainText(data);
    qDebug() << data;

    QScrollBar* sb = ui->textData->verticalScrollBar();
    sb->setValue(sb->maximum());
}

void DataTerminal::Reset() {
    ui->textData->clear();
}

void DataTerminal::WantToSend() {
    emit MustSendLine(ui->commandLine->text() + " \n");
    ui->commandLine->clear();
}
