#include "window/mainwindow.h"
#include <QApplication>
#include <QFile>
#include "util/configuration.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Configuration conf;

    QFile style(":styles/base.css");
    if (style.open(QIODevice::ReadOnly | QIODevice::Text))
        a.setStyleSheet(style.readAll());

    MainWindow w(nullptr, conf);
    w.show();

    return a.exec();
}
