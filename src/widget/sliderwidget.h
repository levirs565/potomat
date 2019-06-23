#ifndef SLIDERWIDGET_H
#define SLIDERWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QSlider>

class SliderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SliderWidget(QWidget *parent = nullptr, QString title = "", QString configName = "",
                          int min = 0, int max = 0, int value = 0);

    QVBoxLayout *layout;
    QLabel *titleLabel;
    QLabel *valueLabel;
    QSlider *slider;

    void setValue(int value);

private:
    QString mConfigName;

signals:
    void valueChanged(QString config, int value);

public slots:
    void sliderValueChanged(int value);
};

#endif // SLIDERWIDGET_H
