#include <QVariant>
#include <QDebug>
#include <QImageReader>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      mCentralWidget(new QWidget(this)),
      mCentralLayout(new QVBoxLayout(mCentralWidget)),
      mTimerWidget(new Timer(mCentralWidget)),
      mTimerButton(new QPushButton(mCentralWidget))
{
    mTimerButton->setProperty("circle", true);
    mTimerButton->setIcon(QIcon(":icons/start.svg"));

    mCentralLayout->addWidget(mTimerWidget, 0, Qt::AlignCenter);
    mCentralLayout->addWidget(mTimerButton, 0, Qt::AlignCenter);

    setStyleSheet("QPushButton[circle=\"true\"] {"
                  " border-width: 2px;"
                  " border-color: #858c99;"
                  " border-style: solid;"
                  " border-radius: 27px;"
                  " width: 50px;"
                  " height: 50px;"
                  " color: #ffffff;"
                  "}"
                  ""
                  "QPushButton[circle=\"true\"]:hover {"
                  " background-color: #3d4457;"
                  "}");

    setCentralWidget(mCentralWidget);
}

MainWindow::~MainWindow()
{

}
