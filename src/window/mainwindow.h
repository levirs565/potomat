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

    static const QString timerArg;
    static const QString roundArg;
    static const QChar zeroChar;

private slots:
    void pomodoro_updateTimer(int remaining, int total);
    void pomodoro_updateRound(Pomodoro::Round round, int runnedRound,
                             int worksRound);
    void pomodoro_updateState(Pomodoro::State state);
    void on_buttonPomodoro_clicked();
    void on_resetButton_clicked();
};

#endif // MAINWINDOW_H
