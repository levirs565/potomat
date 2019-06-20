#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include "../widget/timerwidget.h"
#include "../util/pomodoro.h"
#include "../ui/ui_mainwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Pomodoro *mPomodoro;
    UI_MainWindow *mUI;

private slots:
    void pomodoroUpdateTimer(int remaining, int total);
    void pomodoroUpdateRound(Pomodoro::Round round, int runnedRound,
                             int worksRound);
    void pomodoroUpdateState(Pomodoro::State state);
};

#endif // MAINWINDOW_H
