#include <QVariant>
#include <QDebug>
#include <QImageReader>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent, Configuration& config)
    : QMainWindow(parent),
      mPomodoro(new Pomodoro(this)),
      mUI(new Ui::MainWindow()),
      mConfig(config)
{
//    mPomodoro->loadConfig(mConfig);
//    connect(mPomodoro, &Pomodoro::updateTimer,
//            this, &MainWindow::pomodoroUpdateTimer);
//    connect(mPomodoro, &Pomodoro::updateRound,
//            this, &MainWindow::pomodoroUpdateRound);
//    connect(mPomodoro, &Pomodoro::updateState,
//            this, &MainWindow::pomodoroUpdateState);
//    mPomodoro->startIntegration();

//    mUI->drawerView->configView->setConfiguration(
//                mPomodoro->getConfig(1),
//                mPomodoro->getConfig(2),
//                mPomodoro->getConfig(3),
//                mPomodoro->getConfig(0)
//    );
//    qDebug() << mPomodoro->getConfig(0);
//    connect(mUI->drawerView->configView, &ConfigurationView::configChanged,
//            mPomodoro, &Pomodoro::setConfig);
//    connect(mUI->drawerView->configView->resetButton, &QPushButton::clicked,
//            this, &MainWindow::resetConfig);

//    pomodoroUpdateState(Pomodoro::Idle);

//    setCentralWidget(mUI->centralWidget);

    mUI->setupUi(this);
}

MainWindow::~MainWindow()
{
//    mPomodoro->saveConfig(mConfig);
}

void MainWindow::pomodoroUpdateTimer(int remaining, int total)
{
//    mUI->timerView->setTime(remaining, total);
}

void MainWindow::pomodoroUpdateRound(Pomodoro::Round round, int runnedRound,
                                     int worksRound)
{
//    mUI->timerView->setRound(round, runnedRound, worksRound);
}

void MainWindow::pomodoroUpdateState(Pomodoro::State state)
{
//    const char *buttonSlot = nullptr;
//    const char *resetSlot = nullptr;

//    if (state == Pomodoro::Idle)
//        buttonSlot = SLOT(start());
//    else {
//        if (state == Pomodoro::Paused)
//            buttonSlot = SLOT(resume());
//        else
//            buttonSlot = SLOT(pause());

//        resetSlot = SLOT(resetTimer());
//    }

//    mUI->timerView->setTimerButtonClickSlot(mPomodoro, buttonSlot);
//    mUI->timerView->setResetButtonClickSlot(mPomodoro, resetSlot);
//    mUI->timerView->setState(state);
}

void MainWindow::resetConfig()
{
//    mUI->drawerView->configView->setConfiguration(
//                Pomodoro::defaultTimeWork,
//                Pomodoro::defaultTimeShortBreak,
//                Pomodoro::defaultTimeLongBreak,
//                Pomodoro::defaultWorkRounds
//                );
}

