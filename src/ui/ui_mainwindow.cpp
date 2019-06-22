#include "ui_mainwindow.h"
#include "../util/helper.h"
#include <QWindow>
#include <QWidget>
#include <QVariant>

UI_MainWindow::UI_MainWindow(QMainWindow *parent)
    : QObject(parent),
      centralWidget(new QWidget(parent)),
      centralLayout(new QBoxLayout(QBoxLayout::TopToBottom, centralWidget)),
      timerView(new TimerView(centralWidget))
{
    centralLayout->addWidget(timerView, 0, Qt::AlignTop);
}
