#include "sliderwidget.h"
#include <QDebug>

SliderWidget::SliderWidget(QWidget *parent, QString title, int configIndex, int min,
                           int max, int value)
    : QWidget(parent),
      layout(new QVBoxLayout(this)),
      titleLabel(new QLabel(this)),
      valueLabel(new QLabel(this)),
      slider(new QSlider(Qt::Horizontal, this)),
      mConfigIndex(configIndex)
{
    titleLabel->setText(title);

    connect(slider, &QSlider::valueChanged, this, &SliderWidget::sliderValueChanged);
    slider->setMinimum(min);
    slider->setMaximum(max);
    slider->setValue(value);

    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(titleLabel, 0, Qt::AlignTop | Qt::AlignHCenter);
    layout->addWidget(valueLabel, 0, Qt::AlignTop | Qt::AlignHCenter);
    layout->addWidget(slider, 0, Qt::AlignTop);
}

void SliderWidget::setValue(int value)
{
    slider->setValue(value);
}

void SliderWidget::sliderValueChanged(int value)
{
    valueLabel->setText(QString::number(value));

    emit valueChanged(mConfigIndex, value);
}
