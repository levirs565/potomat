#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QObject>
#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QMainWindow>
#include <QStackedWidget>
#include "../widget/timerwidget.h"
#include "../util/pomodoro.h"
#include "../view/timerview.h"
#include "../view/drawerview.h"

class UI_MainWindow : public QObject
{
    Q_OBJECT
public:
    explicit UI_MainWindow(QMainWindow *parent = nullptr);

    QWidget *centralWidget;
    QBoxLayout *centralLayout;
    QPushButton *toggleButton;
    QStackedWidget *mainWidget;
    TimerView *timerView;
    DrawerView *drawerView;

    bool drawerIsOpened;

signals:

public slots:
    void toggleDrawer();
};

#endif // UI_MAINWINDOW_H
