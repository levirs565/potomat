#include "ui_mainwindow.h"
#include "../util/helper.h"
#include <QWindow>
#include <QWidget>
#include <QVariant>

UI_MainWindow::UI_MainWindow(QMainWindow *parent)
    : QObject(parent),
      centralWidget(new QWidget(parent)),
      centralLayout(new QBoxLayout(QBoxLayout::TopToBottom, centralWidget)),
      toggleButton(new QPushButton(centralWidget)),
      mainWidget(new QStackedWidget(centralWidget)),
      timerView(new TimerView()),
      drawerView(new DrawerView()),
      drawerIsOpened(false)
{
    toggleButton->setText("More");
    connect(toggleButton, SIGNAL(clicked()), this, SLOT(toggleDrawer()));

    mainWidget->addWidget(timerView);
    mainWidget->addWidget(drawerView);
    mainWidget->setCurrentIndex(0);

    centralLayout->addWidget(toggleButton, 0, Qt::AlignLeft | Qt::AlignTop);
    centralLayout->addWidget(mainWidget);
}

void UI_MainWindow::toggleDrawer()
{
    if (drawerIsOpened)
        mainWidget->setCurrentIndex(0);
    else
        mainWidget->setCurrentIndex(1);

    drawerIsOpened = !drawerIsOpened;
}
