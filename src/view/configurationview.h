#ifndef POMODOROCONFIGVIEW_H
#define POMODOROCONFIGVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include "../widget/sliderwidget.h"

class ConfigurationView : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigurationView(QWidget *parent = nullptr);

    QVBoxLayout *layout;
    QLabel *header;
    SliderWidget *workSlider;
    SliderWidget *shortBreakSlider;
    SliderWidget *longBreakSlider;
    SliderWidget *roundsSlider;
    QPushButton *resetButton;

signals:

public slots:
};

#endif // POMODOROCONFIGVIEW_H
