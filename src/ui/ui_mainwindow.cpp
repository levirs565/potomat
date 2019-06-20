#include "ui_mainwindow.h"
#include <QWindow>
#include <QWidget>
#include <QVariant>

UI_MainWindow::UI_MainWindow(QMainWindow *parent)
    : QObject(parent),
      centralWidget(new QWidget(parent)),
      centralLayout(new QVBoxLayout(centralWidget)),
      timerWidget(new TimerWidget(centralWidget)),
      timerButton(new QPushButton(centralWidget)),
      mStartIcon(":icons/start.svg"),
      mPauseIcon(":icons/pause.svg")
{
    timerButton->setProperty("circle", true);

    centralLayout->addWidget(timerWidget, 0, Qt::AlignCenter);
    centralLayout->addWidget(timerButton, 0, Qt::AlignCenter);
}

void UI_MainWindow::setState(Pomodoro::State state)
{
    if (state == Pomodoro::Idle || state == Pomodoro::Paused) {
        timerButton->setIcon(mStartIcon);
    } else {
        timerButton->setIcon(mPauseIcon);
    }
}
