#include "timer.h"
#include <QResizeEvent>
#include <QDebug>

Timer::Timer(QWidget *parent) :
    QWidget(parent),
    mDial(new TimerDial(this)),
    mLabelsWidget(new QWidget(this)),
    mLabelsLayout(new QVBoxLayout(mLabelsWidget)),
    mTimeLabel(new QLabel(mLabelsWidget)),
    mDialLabel(new QLabel(mLabelsWidget))
{
    QFont timeLabelFont("Roboto Mono");
    timeLabelFont.setPixelSize(46);
    timeLabelFont.setStyleHint(QFont::Monospace);
    timeLabelFont.setWeight(QFont::Light);

    mTimeLabel->setFont(timeLabelFont);
    mTimeLabel->setAlignment(Qt::AlignCenter);

    mLabelsLayout->addWidget(mTimeLabel, 0, Qt::AlignCenter);

    QFont dialLabelFont("Lato");
    dialLabelFont.setPixelSize(16);
    dialLabelFont.setCapitalization(QFont::AllUppercase);
    dialLabelFont.setStyleHint(QFont::SansSerif);

    mDialLabel->setFont(dialLabelFont);
    mDialLabel->setText("Work");

    mLabelsLayout->addWidget(mDialLabel, 0, Qt::AlignCenter);

    setFixedSize(220, 220);

    setTime(60*25, 60*25);
}

Timer::~Timer()
{
    delete mDialLabel;
    delete mTimeLabel;
    delete mLabelsLayout;
    delete mLabelsWidget;
    delete mDial;
}

void Timer::setTime(int remaining, int total)
{
    mTimeLabel->setText(formatTime(remaining));
    mDial->setPercent((float)remaining/(float)total);
}

void Timer::setDialFillColor(QColor fill)
{
    mDial->setFillColor(fill);
}

void Timer::resizeEvent(QResizeEvent *event)
{
    const int width = event->size().width();
    const int height = event->size().height();

    mDial->setGeometry(0, 0, width, height);

    const int ch = mLabelsWidget->sizeHint().height();
    const int top = (height/2) - (ch/2);

    mLabelsWidget->setGeometry(0, top, width, ch);
}

const QLatin1Char Timer::zeroChar = QLatin1Char('0');

QString Timer::formatTime(int s)
{
    const int minute = s / 60;
    const int second = s % 60;

    return QString("%1:%2")
            .arg(minute, 2, 10, zeroChar)
            .arg(second, 2, 10, zeroChar);
}
