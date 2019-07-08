#ifndef NOTIFICATIONWIDGET_H
#define NOTIFICATIONWIDGET_H

#include <QWidget>
#include <QPropertyAnimation>

namespace Ui {
class NotificationWidget;
}

class NotificationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NotificationWidget(QWidget *parent = nullptr);
    ~NotificationWidget();

    void setup(QString title, QString description);

public slots:
    void notificationShow();
    void notificationClose();

protected:
    void paintEvent(QPaintEvent* event) override;
    void timerEvent(QTimerEvent* event) override;

private:
    Ui::NotificationWidget *mUI;
    QPropertyAnimation *mAlphaAnimation;
    bool mCloseAfterFinished;
    int mTimerId;

private slots:
    void alphaAnimationFinished();
};

#endif // NOTIFICATIONWIDGET_H
