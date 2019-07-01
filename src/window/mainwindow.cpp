#include <QVariant>
#include <QDebug>
#include <QImageReader>
#include <QMouseEvent>
#include "mainwindow.h"
#include "../widget/swtabbar.h"

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
    maximizeSize();

    setWindowFlag(Qt::FramelessWindowHint);

    mPomodoro->startIntegration();
}

MainWindow::~MainWindow()
{
    mPomodoro->saveConfig(mConfig);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        mLastPoint = event->globalPos() - frameGeometry().topLeft();
        mCanDrag = true;
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        mCanDrag = false;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton && mCanDrag) {
        move(event->globalPos() - mLastPoint);
    }
}

void MainWindow::openDrawer()
{
    mUI->sliderWorkRounds->setValue(mPomodoro->getConfig(0));
    mUI->sliderWork->setValue(mPomodoro->getConfig(1));
    mUI->sliderShortBreak->setValue(mPomodoro->getConfig(2));
    mUI->sliderLongBreak->setValue(mPomodoro->getConfig(3));

    mUI->stackedWidget->setCurrentIndex(1);

    mUI->buttonMinmize->setEnabled(false);
}

void MainWindow::closeDrawer()
{
    mPomodoro->setConfig(0, mUI->sliderWorkRounds->value());
    mPomodoro->setConfig(1, mUI->sliderWork->value());
    mPomodoro->setConfig(2, mUI->sliderShortBreak->value());
    mPomodoro->setConfig(3, mUI->sliderLongBreak->value());

    mUI->stackedWidget->setCurrentIndex(0);

    mUI->buttonMinmize->setEnabled(true);
}

void MainWindow::minimizeSize()
{
    mUI->layoutTimer->setDirection(QBoxLayout::LeftToRight);

    mUI->timerPomodoro->setMinimumSize(0, 0);
    mUI->timerPomodoro->setMaximumSize(100000, 100000);
    mUI->timerPomodoro->setType(TimerProgressWidget::Horizontal);
    mUI->layoutTimer->setAlignment(mUI->timerPomodoro, Qt::Alignment());
    mUI->layoutTimer->setMargin(0);

    mUI->layoutPomodoro->setDirection(QBoxLayout::LeftToRight);
    mUI->u_spacerPomodoro_1->changeSize(0, 0, QSizePolicy::Minimum, QSizePolicy::Fixed);
    mUI->u_spacerPomodoro_2->changeSize(0, 0, QSizePolicy::Minimum, QSizePolicy::Fixed);
    mUI->u_spacerPomodoro_3->changeSize(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);

    mUI->verticalLayout->setDirection(QBoxLayout::LeftToRight);

    mUI->footerLeft->setVisible(false);
    mUI->buttonPomodoro->setVisible(false);

    QFont qf = QFont(mUI->labelTimer->font());
    qf.setPointSize(14);
    mUI->labelTimer->setFont(qf);

    mUI->layoutTopbar->setDirection(QBoxLayout::RightToLeft);
    mUI->u_spacerTopbar->changeSize(0, 0, QSizePolicy::Minimum, QSizePolicy::Fixed);
    mUI->buttonDrawer->setVisible(false);
    mUI->buttonTopPomodoro->setVisible(true);
    mUI->buttonMinmize->setText(QString::fromWCharArray(L"\ue316"));

    setFixedSize(450, 45);

    mIsMinimize = true;
}

void MainWindow::maximizeSize()
{
    mUI->layoutTimer->setDirection(QBoxLayout::TopToBottom);

    mUI->timerPomodoro->setMinimumSize(220, 220);
    mUI->timerPomodoro->setMaximumSize(220, 220);
    mUI->timerPomodoro->setType(TimerProgressWidget::Dial);
    mUI->layoutTimer->setAlignment(mUI->timerPomodoro, Qt::AlignHCenter|Qt::AlignTop);
    mUI->layoutTimer->setMargin(9);

    mUI->layoutPomodoro->setDirection(QBoxLayout::TopToBottom);
    mUI->u_spacerPomodoro_1->changeSize(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    mUI->u_spacerPomodoro_2->changeSize(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    mUI->u_spacerPomodoro_3->changeSize(0, 6, QSizePolicy::Minimum, QSizePolicy::Fixed);

    mUI->verticalLayout->setDirection(QBoxLayout::TopToBottom);

    mUI->footerLeft->setVisible(true);
    mUI->buttonPomodoro->setVisible(true);

    QFont qf = QFont(mUI->labelTimer->font());
    qf.setPointSize(36);
    mUI->labelTimer->setFont(qf);

    mUI->layoutTopbar->setDirection(QBoxLayout::LeftToRight);
    mUI->u_spacerTopbar->changeSize(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    mUI->buttonDrawer->setVisible(true);
    mUI->buttonTopPomodoro->setVisible(false);
    mUI->buttonMinmize->setText(QString::fromWCharArray(L"\ue313"));

    setFixedSize(260, 425);

    mIsMinimize = false;
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
    mUI->buttonTopPomodoro->setText(text);
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

void MainWindow::on_buttonDrawer_clicked()
{
    if (mUI->stackedWidget->currentIndex() == 0)
        openDrawer();
    else
        closeDrawer();
}

void MainWindow::on_buttonMinmize_clicked()
{
    if (!mIsMinimize)
        minimizeSize();
    else
        maximizeSize();
}

void MainWindow::on_buttonTopPomodoro_clicked()
{
    on_buttonPomodoro_clicked();
}
