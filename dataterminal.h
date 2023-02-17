#ifndef DATATERMINAL_H
#define DATATERMINAL_H

#include <QWidget>
#include <QScrollBar>

namespace Ui {
class DataTerminal;
}

class DataTerminal : public QWidget
{
    Q_OBJECT

public:
    explicit DataTerminal(QWidget *parent = nullptr);
    ~DataTerminal();

    void AppendData(QString data);

    void Reset();

public slots:
    void WantToSend();

signals:
    void MustSendLine(QString line);

private:
    Ui::DataTerminal *ui;
};

#endif // DATATERMINAL_H
