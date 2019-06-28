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
    mPomodoro->loadConfig(mConfig);
    connect(mPomodoro, &Pomodoro::updateTimer,
            this, &MainWindow::pomodoro_updateTimer);
    connect(mPomodoro, &Pomodoro::updateRound,
            this, &MainWindow::pomodoro_updateRound);
    connect(mPomodoro, &Pomodoro::updateState,
            this, &MainWindow::pomodoro_updateState);

    mUI->setupUi(this);

    mPomodoro->startIntegration();
}

MainWindow::~MainWindow()
{
    mPomodoro->saveConfig(mConfig);
}

void MainWindow::openDrawer()
{
    mUI->sliderWorkRounds->setValue(mPomodoro->getConfig(0));
    mUI->sliderWork->setValue(mPomodoro->getConfig(1));
    mUI->sliderShortBreak->setValue(mPomodoro->getConfig(2));
    mUI->sliderLongBreak->setValue(mPomodoro->getConfig(3));

    mUI->stackedWidget->setCurrentIndex(1);
}

void MainWindow::closeDrawer()
{
    mPomodoro->setConfig(0, mUI->sliderWorkRounds->value());
    mPomodoro->setConfig(1, mUI->sliderWork->value());
    mPomodoro->setConfig(2, mUI->sliderShortBreak->value());
    mPomodoro->setConfig(3, mUI->sliderLongBreak->value());

    mUI->stackedWidget->setCurrentIndex(0);
}

const QString MainWindow::timerArg = "%1:%2";
const QChar MainWindow::zeroChar = '0';

void MainWindow::pomodoro_updateTimer(int remaining, int total)
{
    const int minute = remaining / 60;
    const int second = remaining % 60;

    mUI->labelTimer->setText(timerArg
                                .arg(minute, 2, 10, zeroChar)
                                .arg(second, 2, 10, zeroChar));

    mUI->timerPomodoro->setPercent((float)remaining/(float)total);
}

const QString MainWindow::roundArg = "%1/%2";

void MainWindow::pomodoro_updateRound(Pomodoro::Round round, int runnedRound,
                                     int worksRound)
{
    QString roundName;
    if (round == Pomodoro::Work)
        roundName = "Work";
    else if (round == Pomodoro::ShortBreak)
        roundName  = "Short Break";
    else
        roundName = "Long Break";

    mUI->labelRoundName->setText(roundName);
    mUI->labelRound->setText(roundArg
                                .arg(runnedRound)
                                .arg(worksRound));
}

void MainWindow::pomodoro_updateState(Pomodoro::State state)
{
    QString text;

    if (state == Pomodoro::Idle || state == Pomodoro::Paused)
        text = QString::fromWCharArray(L"\ue037");
    else
        text = QString::fromWCharArray(L"\ue034");

    mUI->buttonPomodoro->setText(text);
}

void MainWindow::on_buttonPomodoro_clicked()
{
    Pomodoro::State state = mPomodoro->getCurrentState();

    if (state == Pomodoro::Idle)
        mPomodoro->start();
    else if (state == Pomodoro::Paused)
        mPomodoro->resume();
    else if (state == Pomodoro::Started)
        mPomodoro->pause();
}

void MainWindow::on_resetButton_clicked()
{
    if (mPomodoro->getCurrentState() != Pomodoro::Idle)
        mPomodoro->resetTimer();
}

void MainWindow::on_pushButton_clicked()
{
    if (mUI->stackedWidget->currentIndex() == 0)
        openDrawer();
    else
        closeDrawer();
}
