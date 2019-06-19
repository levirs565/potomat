#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include "../widget/timerwidget.h"
#include "../util/pomodoro.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Pomodoro *mPomodoro;
    QWidget *mCentralWidget;
    QVBoxLayout *mCentralLayout;
    TimerWidget *mTimerWidget;
    QPushButton *mTimerButton;
    QIcon mStartIcon;
    QIcon mPauseIcon;

private slots:
    void pomodoroUpdateTimer(int remaining, int total);
    void pomodoroUpdateRound(Pomodoro::Round round, int runnedRound);
    void pomodoroUpdateState(Pomodoro::State state);
};

#endif // MAINWINDOW_H
