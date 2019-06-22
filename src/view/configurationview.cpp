#include "configurationview.h"

ConfigurationView::ConfigurationView(QWidget *parent)
    : QWidget(parent),
      layout(new QVBoxLayout(this)),
      header(new QLabel(this)),
      workSlider(new SliderWidget(this, "Work", 1, 60, 25)),
      shortBreakSlider(new SliderWidget(this, "Short Break", 1, 60, 5)),
      longBreakSlider(new SliderWidget(this, "Long Break", 1, 60, 15)),
      roundsSlider(new SliderWidget(this, "Rounds", 1, 12, 4)),
      resetButton(new QPushButton(this))
{
    header->setText("Timer");

    resetButton->setText("Reset Defaults");

    layout->addWidget(header, 0, Qt::AlignTop | Qt::AlignHCenter);
    layout->addWidget(workSlider, 0, Qt::AlignTop);
    layout->addWidget(shortBreakSlider, 0, Qt::AlignTop);
    layout->addWidget(longBreakSlider, 0, Qt::AlignTop);
    layout->addWidget(roundsSlider, 0, Qt::AlignTop);
    layout->addWidget(resetButton, 0, Qt::AlignTop);
}
