#include <QVariant>
#include <QDebug>
#include <QImageReader>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      mPomodoro(new Pomodoro(this)),
      mCentralWidget(new QWidget(this)),
      mCentralLayout(new QVBoxLayout(mCentralWidget)),
      mTimerWidget(new TimerWidget(mCentralWidget)),
      mTimerButton(new QPushButton(mCentralWidget)),
      mStartIcon(":icons/start.svg"),
      mPauseIcon(":icons/pause.svg")
{
    connect(mPomodoro, &Pomodoro::updateTimer,
            this, &MainWindow::pomodoroUpdateTimer);
    connect(mPomodoro, &Pomodoro::updateRound,
            this, &MainWindow::pomodoroUpdateRound);
    connect(mPomodoro, &Pomodoro::updateState,
            this, &MainWindow::pomodoroUpdateState);

    mTimerButton->setProperty("circle", true);
    pomodoroUpdateState(Pomodoro::Idle);

    mCentralLayout->addWidget(mTimerWidget, 0, Qt::AlignCenter);
    mCentralLayout->addWidget(mTimerButton, 0, Qt::AlignCenter);

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

    setCentralWidget(mCentralWidget);
}

MainWindow::~MainWindow()
{

}

void MainWindow::pomodoroUpdateTimer(int remaining, int total)
{
    mTimerWidget->setTime(remaining, total);
}

void MainWindow::pomodoroUpdateRound(Pomodoro::Round round, int runnedRound)
{
    QString str = Pomodoro::roundToString(round);
    mTimerWidget->setLabel(str);
}

void MainWindow::pomodoroUpdateState(Pomodoro::State state)
{
    mTimerButton->disconnect(SIGNAL(clicked()));

    if (state == Pomodoro::Idle || state == Pomodoro::Paused) {
        if (state == Pomodoro::Idle)
            connect(mTimerButton, SIGNAL(clicked()),
                    mPomodoro, SLOT(start()));
        else
            connect(mTimerButton, SIGNAL(clicked()),
                    mPomodoro, SLOT(resume()));

        mTimerButton->setIcon(mStartIcon);
    } else {
        connect(mTimerButton, SIGNAL(clicked()),
                mPomodoro, SLOT(pause()));
        mTimerButton->setIcon(mPauseIcon);
    }
}
