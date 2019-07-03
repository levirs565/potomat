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
      mMediaPlayer(new QMediaPlayer(this)),
      mConfig(config),
      mAfterStartUp(false)
{
    mPomodoro->loadConfig(mConfig);
    loadConfig();

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

    mAfterStartUp = true;
}

MainWindow::~MainWindow()
{
    mPomodoro->saveConfig(mConfig);
    saveConfig();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        mLastPoint = event->globalPos() - frameGeometry().topLeft();
        mCanDrag = true;
        event->accept();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        mCanDrag = false;
        event->accept();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton && mCanDrag) {
        move(event->globalPos() - mLastPoint);
        event->accept();
    }
}

void MainWindow::setAlwaysOnTop(bool alwaysOnTop)
{
    if (alwaysOnTop == mAlwaysOnTop)
        return;

    mAlwaysOnTop = alwaysOnTop;
    setWindowFlag(Qt::WindowStaysOnTopHint, mAlwaysOnTop);

    if (mAfterStartUp)
        show();
}

void MainWindow::openDrawer()
{
    mUI->sliderWorkRounds->setValue(mPomodoro->getConfig(0));
    mUI->sliderWork->setValue(mPomodoro->getConfig(1));
    mUI->sliderShortBreak->setValue(mPomodoro->getConfig(2));
    mUI->sliderLongBreak->setValue(mPomodoro->getConfig(3));

    mUI->checkAlwaysOnTop->setChecked(mAlwaysOnTop);
    mUI->checkPlayAudio->setChecked(mPlayAudio);

    mUI->stackedWidget->setCurrentIndex(1);

    mUI->buttonExpand->setEnabled(false);
}

void MainWindow::closeDrawer()
{
    mPomodoro->setConfig(0, mUI->sliderWorkRounds->value());
    mPomodoro->setConfig(1, mUI->sliderWork->value());
    mPomodoro->setConfig(2, mUI->sliderShortBreak->value());
    mPomodoro->setConfig(3, mUI->sliderLongBreak->value());

    setAlwaysOnTop(mUI->checkAlwaysOnTop->isChecked());
    mPlayAudio = mUI->checkPlayAudio->isChecked();

    mUI->stackedWidget->setCurrentIndex(0);

    mUI->buttonExpand->setEnabled(true);
}

const QString& MainWindow::materialIconExpand = QString::fromWCharArray(L"\ue316");

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
    mUI->u_spacerTopbar_2->changeSize(0, 0, QSizePolicy::Minimum, QSizePolicy::Fixed);
    mUI->buttonDrawer->setVisible(false);
    mUI->buttonTopPomodoro->setVisible(true);
    mUI->u_labelTitle->setVisible(false);
    mUI->buttonExpand->setText(materialIconExpand);

    setFixedSize(450, 45);

    mIsMinimize = true;
}

const QString& MainWindow::materialIconCollapse = QString::fromWCharArray(L"\ue313");

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
    mUI->u_spacerTopbar_2->changeSize(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    mUI->buttonDrawer->setVisible(true);
    mUI->buttonTopPomodoro->setVisible(false);
    mUI->u_labelTitle->setVisible(true);
    mUI->buttonExpand->setText(materialIconCollapse);

    setFixedSize(260, 425);

    mIsMinimize = false;
}

const QString& MainWindow::configAlwaysOnTop = "alwaysOnTop";
const QString& MainWindow::configPlayAudio = "palyAudio";

void MainWindow::loadConfig()
{
    QVariant var;

    var = mConfig.getConfig(configAlwaysOnTop);
    if (var.convert(QVariant::Bool))
        setAlwaysOnTop(var.toBool());
    else
        setAlwaysOnTop(true);

    var = mConfig.getConfig(configPlayAudio);
    if (var.convert(QVariant::Bool))
        mPlayAudio = var.toBool();
    else
        mPlayAudio = true;
}

void MainWindow::saveConfig()
{
    mConfig.setConfig(configAlwaysOnTop, mAlwaysOnTop);
    mConfig.setConfig(configPlayAudio, mPlayAudio);
}

const QString& MainWindow::timerArg = "%1:%2";
const QChar& MainWindow::zeroChar = '0';

void MainWindow::pomodoro_updateTimer(int remaining, int total)
{
    const int minute = remaining / 60;
    const int second = remaining % 60;

    mUI->labelTimer->setText(timerArg
                                .arg(minute, 2, 10, zeroChar)
                                .arg(second, 2, 10, zeroChar));

    mUI->timerPomodoro->setPercent((float)remaining/(float)total);
}

const QString& MainWindow::roundArg = "%1/%2";
const QUrl MainWindow::mediaWork = QUrl("qrc:/audios/capisci.mp3");
const QUrl MainWindow::mediaShortBreak = QUrl("qrc:/audios/isnt-it.mp3");
const QUrl MainWindow::mediaLongBreak = QUrl("qrc:/audios/springtime.mp3");

void MainWindow::pomodoro_updateRound(Pomodoro::Round round, int runnedRound,
                                     int worksRound)
{
    QString roundName;
    QUrl mUrl;

    if (round == Pomodoro::Work) {
        roundName = "Work";
        mUrl = mediaWork;
    } else if (round == Pomodoro::ShortBreak) {
        roundName  = "Short Break";
        mUrl = mediaShortBreak;
    } else {
        roundName = "Long Break";
        mUrl = mediaLongBreak;
    }

    mUI->labelRoundName->setText(roundName);
    mUI->labelRound->setText(roundArg
                                .arg(runnedRound)
                                .arg(worksRound));

    if (mPlayAudio && runnedRound > 0 && mLastRound != round) {
        mMediaPlayer->setMedia(mUrl);
        mMediaPlayer->play();

        mLastRound = round;
    }
}

const QString& MainWindow::materialIconPlay = QString::fromWCharArray(L"\ue037");
const QString& MainWindow::materialIconPause = QString::fromWCharArray(L"\ue034");

void MainWindow::pomodoro_updateState(Pomodoro::State state)
{
    QString text;

    if (state == Pomodoro::Idle || state == Pomodoro::Paused)
        text = materialIconPlay;
    else
        text = materialIconPause;

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

void MainWindow::on_buttonTopPomodoro_clicked()
{
    on_buttonPomodoro_clicked();
}

void MainWindow::on_buttonExpand_clicked()
{
    if (!mIsMinimize)
        minimizeSize();
    else
        maximizeSize();
}
