#ifndef TIMERVIEW_H
#define TIMERVIEW_H

#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
#include "../widget/timerwidget.h"
#include "../util/pomodoro.h"

class TimerView : public QWidget
{
    Q_OBJECT
public:
    explicit TimerView(QWidget *parent = nullptr);

    QVBoxLayout *centralLayout;
    TimerWidget *timerWidget;
    QPushButton *timerButton;

    QWidget *footerWidget;
    QHBoxLayout *footerLayout;
    QWidget *footerLeftWidget;
    QVBoxLayout *footerLeftLayout;
    QLabel *footerLeftRoundLabel;
    QPushButton *footerLeftResetButton;

    void setState(Pomodoro::State state);
    void setRound(Pomodoro::Round round, int runnedRound,
                  int worksRound);
    void setTime(int remainingTime, int totalTimer);
    void setTimerButtonClickSlot(QObject *receiver, const char* amember);
    void setResetButtonClickSlot(QObject *receiver, const char* amember);

private:
    QIcon mStartIcon;
    QIcon mPauseIcon;

signals:

public slots:
};

#endif // TIMERVIEW_H
