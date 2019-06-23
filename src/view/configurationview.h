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

    void setConfiguration(int timeWork, int timeShortBreak, int timeLongBreak, int workRounds);

signals:
    void configChanged(int config, int value);

private slots:
    void valueChanged(int config, int value);
};

#endif // POMODOROCONFIGVIEW_H
