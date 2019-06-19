#ifndef TIMER_H
#define TIMER_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "timerdial.h"

class Timer : public QWidget
{
    Q_OBJECT
public:
    explicit Timer(QWidget *parent = nullptr);
    ~Timer() override;

    void setTime(int remaining, int total);
    void setDialFillColor(QColor fill);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    TimerDial *mDial;
    QLayout *mLayout;
    QWidget *mLabelsWidget;
    QVBoxLayout *mLabelsLayout;
    QLabel *mTimeLabel;
    QLabel *mDialLabel;

    static const QLatin1Char zeroChar;

    static QString formatTime(int s);

signals:

public slots:
};

#endif // TIMER_H
