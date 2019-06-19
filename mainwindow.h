#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include "timer.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QWidget *mCentralWidget;
    QVBoxLayout *mCentralLayout;
    Timer *mTimerWidget;
    QPushButton *mTimerButton;
};

#endif // MAINWINDOW_H
