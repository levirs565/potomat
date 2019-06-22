#include <QVariant>
#include <QDebug>
#include <QImageReader>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      mPomodoro(new Pomodoro(this)),
      mUI(new UI_MainWindow(this))
{
    connect(mPomodoro, &Pomodoro::updateTimer,
            this, &MainWindow::pomodoroUpdateTimer);
    connect(mPomodoro, &Pomodoro::updateRound,
            this, &MainWindow::pomodoroUpdateRound);
    connect(mPomodoro, &Pomodoro::updateState,
            this, &MainWindow::pomodoroUpdateState);
    mPomodoro->startIntegration();

    pomodoroUpdateState(Pomodoro::Idle);

    setCentralWidget(mUI->centralWidget);
}

MainWindow::~MainWindow()
{

}

void MainWindow::pomodoroUpdateTimer(int remaining, int total)
{
    mUI->timerView->setTime(remaining, total);
}

void MainWindow::pomodoroUpdateRound(Pomodoro::Round round, int runnedRound,
                                     int worksRound)
{
    mUI->timerView->setRound(round, runnedRound, worksRound);
}

void MainWindow::pomodoroUpdateState(Pomodoro::State state)
{
    const char *buttonSlot = nullptr;
    const char *resetSlot = nullptr;

    if (state == Pomodoro::Idle)
        buttonSlot = SLOT(start());
    else {
        if (state == Pomodoro::Paused)
            buttonSlot = SLOT(resume());
        else
            buttonSlot = SLOT(pause());

        resetSlot = SLOT(resetTimer());
    }


    mUI->timerView->setTimerButtonClickSlot(mPomodoro, buttonSlot);
    mUI->timerView->setResetButtonClickSlot(mPomodoro, resetSlot);
    mUI->timerView->setState(state);
}

