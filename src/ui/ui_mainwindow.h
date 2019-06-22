#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QObject>
#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QMainWindow>
#include "../widget/timerwidget.h"
#include "../util/pomodoro.h"
#include "../view/timerview.h"

class UI_MainWindow : public QObject
{
    Q_OBJECT
public:
    explicit UI_MainWindow(QMainWindow *parent = nullptr);

    QWidget *centralWidget;
    QBoxLayout *centralLayout;
    TimerView *timerView;

signals:

public slots:
};

#endif // UI_MAINWINDOW_H
