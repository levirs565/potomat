#include "ui_mainwindow.h"
#include "../util/helper.h"
#include <QWindow>
#include <QWidget>
#include <QVariant>

UI_MainWindow::UI_MainWindow(QMainWindow *parent)
    : QObject(parent),
      centralWidget(new QWidget(parent)),
      centralLayout(new QVBoxLayout(centralWidget)),
      timerWidget(new TimerWidget(centralWidget)),
      timerButton(new QPushButton(centralWidget)),

      footerWidget(new QWidget(centralWidget)),
      footerLayout(new QHBoxLayout(footerWidget)),
      footerLeftWidget(new QWidget(footerWidget)),
      footerLeftLayout(new QVBoxLayout(footerLeftWidget)),
      footerLeftLabelWidget(new QLabel(footerLeftWidget)),
      footerLeftButtonWidget(new QPushButton(footerLeftWidget)),

      mStartIcon(":icons/start.svg"),
      mPauseIcon(":icons/pause.svg")
{
    QFont baseFont("Lato");
    baseFont.setPixelSize(16);
    baseFont.setStyleHint(QFont::SansSerif);

    timerButton->setProperty("circle", true);

    footerLeftLabelWidget->setFont(baseFont);

    footerLeftButtonWidget->setText("Reset");
    footerLeftButtonWidget->setFont(baseFont);

    footerLeftLayout->setContentsMargins(0, 0, 0, 0);
    footerLeftLayout->addWidget(footerLeftLabelWidget, 0, Qt::AlignCenter);
    footerLeftLayout->addWidget(footerLeftButtonWidget, 0, Qt::AlignCenter);

    footerLayout->setContentsMargins(0, 0, 0, 0);
    footerLayout->addWidget(footerLeftWidget, 0, Qt::AlignLeft);

    centralLayout->addWidget(timerWidget, 0, Qt::AlignCenter);
    centralLayout->addWidget(timerButton, 0, Qt::AlignCenter);
    centralLayout->addWidget(footerWidget, 0, Qt::AlignVCenter);
}

void UI_MainWindow::setState(Pomodoro::State state)
{
    if (state == Pomodoro::Idle || state == Pomodoro::Paused) {
        timerButton->setIcon(mStartIcon);
    } else {
        timerButton->setIcon(mPauseIcon);
    }
}

void UI_MainWindow::setRound(Pomodoro::Round round, int runnedRound, int worksRound)
{
    QString label;

    if (round == Pomodoro::Work)
        label = "Work";
    else if (round == Pomodoro::ShortBreak)
        label = "Short Break";
    else
        label = "Long Break";

    timerWidget->setLabel(label);
    footerLeftLabelWidget->setText(
                QString("%1/%2")
                    .arg(runnedRound)
                .arg(worksRound));
}

void UI_MainWindow::setTime(int remainingTime, int totalTimer)
{
    timerWidget->setTime(remainingTime, totalTimer);
}

void UI_MainWindow::setTimerButtonClickSlot(QObject *receiver, const char *amember)
{
    setConnection(timerButton, SIGNAL(clicked()), receiver, amember);
}

void UI_MainWindow::setResetButtonClickSlot(QObject *receiver, const char *amember)
{
    setConnection(footerLeftButtonWidget, SIGNAL(clicked()), receiver, amember);
}
