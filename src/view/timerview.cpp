#include "timerview.h"
#include "../util/helper.h"
#include <QVariant>

TimerView::TimerView(QWidget *parent)
    : QWidget(parent),
      centralLayout(new QVBoxLayout(this)),
      timerWidget(new TimerWidget(this)),
      timerButton(new QPushButton(this)),

      footerWidget(new QWidget(this)),
      footerLayout(new QHBoxLayout(footerWidget)),
      footerLeftWidget(new QWidget(footerWidget)),
      footerLeftLayout(new QVBoxLayout(footerLeftWidget)),
      footerLeftRoundLabel(new QLabel(footerLeftWidget)),
      footerLeftResetButton(new QPushButton(footerLeftWidget))
{
    QFont baseFont("Lato");
    baseFont.setPixelSize(16);
    baseFont.setStyleHint(QFont::SansSerif);

    timerButton->setProperty("circle", true);
    timerButton->setProperty("material-icon", true);

    footerLeftRoundLabel->setFont(baseFont);

    footerLeftResetButton->setText("Reset");
    footerLeftResetButton->setFont(baseFont);

    footerLeftLayout->setContentsMargins(0, 0, 0, 0);
    footerLeftLayout->addWidget(footerLeftRoundLabel, 0, Qt::AlignCenter);
    footerLeftLayout->addWidget(footerLeftResetButton, 0, Qt::AlignCenter);

    footerLayout->setContentsMargins(0, 0, 0, 0);
    footerLayout->addWidget(footerLeftWidget, 0, Qt::AlignLeft);

    centralLayout->setContentsMargins(0, 0, 0, 0);
    centralLayout->addWidget(timerWidget, 0, Qt::AlignCenter);
    centralLayout->addWidget(timerButton, 0, Qt::AlignCenter);
    centralLayout->addWidget(footerWidget, 0, Qt::AlignVCenter);
}

const QString& TimerView::materialPlayIcon = QString::fromWCharArray(L"\ue037");
const QString& TimerView::materialPauseIcon = QString::fromWCharArray(L"\ue034");

void TimerView::setState(Pomodoro::State state)
{
    if (state == Pomodoro::Idle || state == Pomodoro::Paused) {
        timerButton->setText(materialPlayIcon);
    } else {
        timerButton->setText(materialPauseIcon);
    }
}

void TimerView::setRound(Pomodoro::Round round, int runnedRound, int worksRound)
{
    QString label;

    if (round == Pomodoro::Work)
        label = "Work";
    else if (round == Pomodoro::ShortBreak)
        label = "Short Break";
    else
        label = "Long Break";

    timerWidget->setLabel(label);
    footerLeftRoundLabel->setText(
                QString("%1/%2")
                    .arg(runnedRound)
                .arg(worksRound));
}

void TimerView::setTime(int remainingTime, int totalTimer)
{
    timerWidget->setTime(remainingTime, totalTimer);
}

void TimerView::setTimerButtonClickSlot(QObject *receiver, const char *amember)
{
    setConnection(timerButton, SIGNAL(clicked()), receiver, amember);
}

void TimerView::setResetButtonClickSlot(QObject *receiver, const char *amember)
{
    setConnection(footerLeftResetButton, SIGNAL(clicked()), receiver, amember);
}
