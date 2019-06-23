#include "configurationview.h"
#include <QDebug>

ConfigurationView::ConfigurationView(QWidget *parent)
    : QWidget(parent),
      layout(new QVBoxLayout(this)),
      header(new QLabel(this)),
      workSlider(new SliderWidget(this, "Work", "timeWork", 1, 60, 25)),
      shortBreakSlider(new SliderWidget(this, "Short Break", "timeShortBreak", 1, 60, 5)),
      longBreakSlider(new SliderWidget(this, "Long Break", "timerLongBreak", 1, 60, 15)),
      roundsSlider(new SliderWidget(this, "Rounds", "workRounds", 1, 12, 4)),
      resetButton(new QPushButton(this))
{
    header->setText("Timer");

    resetButton->setText("Reset Defaults");

    const char *signal = SIGNAL(valueChanged(QString,int));
    const char *slot = SLOT(valueChanged(QString,int));

    connect(workSlider, signal, this, slot);
    connect(shortBreakSlider, signal, this, slot);
    connect(longBreakSlider, signal, this, slot);
    connect(roundsSlider, signal, this, slot);

    layout->addWidget(header, 0, Qt::AlignTop | Qt::AlignHCenter);
    layout->addWidget(workSlider, 0, Qt::AlignTop);
    layout->addWidget(shortBreakSlider, 0, Qt::AlignTop);
    layout->addWidget(longBreakSlider, 0, Qt::AlignTop);
    layout->addWidget(roundsSlider, 0, Qt::AlignTop);
    layout->addWidget(resetButton, 0, Qt::AlignTop);
}

void ConfigurationView::setConfiguration(int timeWork, int timeShortBreak, int timeLongBreak,
                                         int workRounds)
{
    workSlider->setValue(timeWork);
    shortBreakSlider->setValue(timeShortBreak);
    longBreakSlider->setValue(timeLongBreak);
    roundsSlider->setValue(workRounds);
}

void ConfigurationView::valueChanged(QString config, int value)
{
    emit configChanged(config, value);
}
