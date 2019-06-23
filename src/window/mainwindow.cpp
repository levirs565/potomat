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

    mUI->drawerView->configView->setConfiguration(
                mPomodoro->getConfig(1),
                mPomodoro->getConfig(2),
                mPomodoro->getConfig(3),
                mPomodoro->getConfig(0)
    );
    connect(mUI->drawerView->configView, SIGNAL(configChanged(int,int)),
            mPomodoro, SLOT(setConfig(int,int)));
    connect(mUI->drawerView->configView->resetButton, SIGNAL(clicked()),
            this, SLOT(resetConfig()));

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

void MainWindow::resetConfig()
{
    mUI->drawerView->configView->setConfiguration(
                Pomodoro::defaultTimeWork,
                Pomodoro::defaultTimeShortBreak,
                Pomodoro::defaultTimeLongBreak,
                Pomodoro::defaultWorkRounds
                );
}

