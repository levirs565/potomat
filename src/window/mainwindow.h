#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include "../widget/timerwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QWidget *mCentralWidget;
    QVBoxLayout *mCentralLayout;
    TimerWidget *mTimerWidget;
    QPushButton *mTimerButton;
};

#endif // MAINWINDOW_H
