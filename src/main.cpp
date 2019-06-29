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

    MainWindow w(nullptr, conf);
    w.show();

    return a.exec();
}
