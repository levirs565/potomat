#include "window/mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QFontDatabase>
#include <QDebug>
#include "util/configuration.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Configuration conf;

    if (QFontDatabase::addApplicationFont(":fonts/MaterialIcons-Regular.ttf") == -1)
        qWarning() << "Cannot load material icons font";

        QFile style(":styles/dark.css");
        if (style.open(QIODevice::ReadOnly | QIODevice::Text)) {
            a.setStyleSheet(style.readAll());
            style.close();
        } else {
            qWarning() << "Cannot load styles";
        }

    MainWindow w(nullptr, conf);
    w.show();

    return a.exec();
}
