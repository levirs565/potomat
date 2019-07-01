#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include "../widget/timerwidget.h"
#include "../util/pomodoro.h"
#include "../util/configuration.h"
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0, Configuration& config = *new Configuration());
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    Pomodoro *mPomodoro;
    Ui::MainWindow *mUI;
    Configuration& mConfig;
    bool mIsMinimize;
    bool mCanDrag;
    QPoint mLastPoint;

    void openDrawer();
    void closeDrawer();
    void minimizeSize();
    void maximizeSize();

    static const QString& materialIconExpand;
    static const QString& materialIconCollapse;
    static const QString& materialIconPlay;
    static const QString& materialIconPause;
    static const QString& timerArg;
    static const QString& roundArg;
    static const QChar& zeroChar;

private slots:
    void pomodoro_updateTimer(int remaining, int total);
    void pomodoro_updateRound(Pomodoro::Round round, int runnedRound,
                             int worksRound);
    void pomodoro_updateState(Pomodoro::State state);
    void on_buttonPomodoro_clicked();
    void on_resetButton_clicked();
    void on_buttonDrawer_clicked();
    void on_buttonMinmize_clicked();
    void on_buttonTopPomodoro_clicked();
};

#endif // MAINWINDOW_H
