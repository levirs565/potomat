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

    setStyleSheet("QPushButton[circle=\"true\"] {"
                  " border-width: 2px;"
                  " border-color: #858c99;"
                  " border-style: solid;"
                  " border-radius: 27px;"
                  " width: 50px;"
                  " height: 50px;"
                  " color: #ffffff;"
                  "}"
                  ""
                  "QPushButton[circle=\"true\"]:hover {"
                  " background-color: #3d4457;"
                  "}");

    setCentralWidget(mUI->centralWidget);
}

MainWindow::~MainWindow()
{

}

void MainWindow::pomodoroUpdateTimer(int remaining, int total)
{
    mUI->timerWidget->setTime(remaining, total);
}

void MainWindow::pomodoroUpdateRound(Pomodoro::Round round, int runnedRound)
{
    QString str = Pomodoro::roundToString(round);
    mUI->timerWidget->setLabel(str);
}

void MainWindow::pomodoroUpdateState(Pomodoro::State state)
{
    mUI->timerButton->disconnect(SIGNAL(clicked()));

    const char *amember;

    if (state == Pomodoro::Idle)
        amember = SLOT(start());
    else if (state == Pomodoro::Paused)
        amember = SLOT(resume());
    else
        amember = SLOT(pause());


    connect(mUI->timerButton, SIGNAL(clicked()), mPomodoro, amember);
    mUI->setState(state);
}
