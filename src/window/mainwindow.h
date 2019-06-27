#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include "../widget/timerwidget.h"
#include "../util/pomodoro.h"
#include "../util/configuration.h"
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0, Configuration& config = *new Configuration());
    ~MainWindow();

private:
    Pomodoro *mPomodoro;
    Ui::MainWindow *mUI;
    Configuration& mConfig;

private slots:
    void pomodoroUpdateTimer(int remaining, int total);
    void pomodoroUpdateRound(Pomodoro::Round round, int runnedRound,
                             int worksRound);
    void pomodoroUpdateState(Pomodoro::State state);
    void resetConfig();
};

#endif // MAINWINDOW_H
