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
    mUI->timerWidget->setTime(remaining, total);
}

void MainWindow::pomodoroUpdateRound(Pomodoro::Round round, int runnedRound,
                                     int worksRound)
{
    QString str = Pomodoro::roundToString(round);
    mUI->timerWidget->setLabel(str);
    mUI->footerLeftLabelWidget->setText(
                QString("%1/%2")
                    .arg(runnedRound)
                    .arg(worksRound));
}

void MainWindow::pomodoroUpdateState(Pomodoro::State state)
{
    mUI->timerButton->disconnect(SIGNAL(clicked()));
    mUI->footerLeftButtonWidget->disconnect(SIGNAL(clicked()));

    const char *amember;

    if (state == Pomodoro::Idle)
        amember = SLOT(start());
    else {
        if (state == Pomodoro::Paused)
            amember = SLOT(resume());
        else
            amember = SLOT(pause());

        connect(mUI->footerLeftButtonWidget, SIGNAL(clicked()),
                mPomodoro, SLOT(resetTimer()));
    }


    connect(mUI->timerButton, SIGNAL(clicked()), mPomodoro, amember);
    mUI->setState(state);
}

