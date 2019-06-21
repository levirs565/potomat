#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QObject>
#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QMainWindow>
#include "../widget/timerwidget.h"
#include "../util/pomodoro.h"

class UI_MainWindow : public QObject
{
    Q_OBJECT
public:
    explicit UI_MainWindow(QMainWindow *parent = nullptr);

    QWidget *centralWidget;
    QVBoxLayout *centralLayout;
    TimerWidget *timerWidget;
    QPushButton *timerButton;

    QWidget *footerWidget;
    QHBoxLayout *footerLayout;
    QWidget *footerLeftWidget;
    QVBoxLayout *footerLeftLayout;
    QLabel *footerLeftLabelWidget;
    QPushButton *footerLeftButtonWidget;

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

#endif // UI_MAINWINDOW_H
