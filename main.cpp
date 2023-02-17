#include <QApplication>
#include "robotcontrol.h"

#include <clocale>


int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    std::setlocale(LC_NUMERIC, "C");

    RobotControl ctrl = RobotControl();
    ctrl.show();

    return app.exec();
}
