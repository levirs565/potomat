#include "sliderwidget.h"

SliderWidget::SliderWidget(QWidget *parent, QString title, int min, int max,
                           int value)
    : QWidget(parent),
      layout(new QVBoxLayout(this)),
      titleLabel(new QLabel(this)),
      valueLabel(new QLabel(this)),
      slider(new QSlider(Qt::Horizontal, this))
{
    titleLabel->setText(title);

    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(sliderValueChanged(int)));
    slider->setMinimum(min);
    slider->setMaximum(max);
    slider->setValue(value);

    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(titleLabel, 0, Qt::AlignTop | Qt::AlignHCenter);
    layout->addWidget(valueLabel, 0, Qt::AlignTop | Qt::AlignHCenter);
    layout->addWidget(slider, 0, Qt::AlignTop);
}

void SliderWidget::sliderValueChanged(int value)
{
    valueLabel->setText(QString::number(value));
}
