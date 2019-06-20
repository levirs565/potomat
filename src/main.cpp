#include "window/mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile style(":styles/base.css");
    if (style.open(QIODevice::ReadOnly | QIODevice::Text))
        a.setStyleSheet(style.readAll());

    MainWindow w;
    w.show();

    return a.exec();
}
