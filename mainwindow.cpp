#include <QVariant>
#include <QDebug>
#include <QImageReader>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      mCentralWidget(new QWidget(this)),
      mCentralLayout(new QVBoxLayout(mCentralWidget)),
      mTimerWidget(new Timer(mCentralWidget))
{

    mCentralLayout->addWidget(mTimerWidget, 0, Qt::AlignCenter);

    setCentralWidget(mCentralWidget);
}

MainWindow::~MainWindow()
{

}
