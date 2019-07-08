#include "notificationwidget.h"
#include "ui_notificationwidget.h"
#include <QScreen>
#include <QStyleOption>
#include <QPainter>
#include <QTimer>
#include <QDebug>

NotificationWidget::NotificationWidget(QWidget *parent) :
    QWidget(parent),
    mUI(new Ui::NotificationWidget),
    mAlphaAnimation(new QPropertyAnimation(this, "windowOpacity")),
    mCloseAfterFinished(false)
{
    mUI->setupUi(this);

    setWindowOpacity(0.0);

    setWindowFlags(Qt::WindowFlags(Qt::FramelessWindowHint)
        | Qt::WindowStaysOnTopHint
        | Qt::BypassWindowManagerHint
        | Qt::NoDropShadowWindowHint
        | Qt::Tool);
    setAttribute(Qt::WA_MacAlwaysShowToolWindow);
    setAttribute(Qt::WA_OpaquePaintEvent);

    mAlphaAnimation->setDuration(500);
    mAlphaAnimation->setStartValue(0.0);
    mAlphaAnimation->setEndValue(1.0);
    connect(mAlphaAnimation, &QPropertyAnimation::finished,
            this, &NotificationWidget::alphaAnimationFinished);

    QRect r = QGuiApplication::screens()[0]->availableGeometry();
    QPoint pos;
    pos.setX(r.x() + r.width() - width() - 6);
    pos.setY(r.y() + 7);

    move(pos);
}

NotificationWidget::~NotificationWidget()
{
    delete mUI;
}

void NotificationWidget::setup(QString title, QString description)
{
    mUI->labelTitle->setText(title);
    mUI->labelDescription->setText(description);
}

void NotificationWidget::notificationShow()
{
    mCloseAfterFinished = false;

    show();
    mAlphaAnimation->stop();
    mAlphaAnimation->setDirection(QAbstractAnimation::Forward);
    mAlphaAnimation->start();

    QTimer::singleShot(2000, this, &NotificationWidget::notificationClose);
}

void NotificationWidget::notificationClose()
{
    mCloseAfterFinished = true;

    mAlphaAnimation->stop();
    mAlphaAnimation->setDirection(QAbstractAnimation::Backward);
    mAlphaAnimation->start();
}

void NotificationWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    p.end();
}

void NotificationWidget::timerEvent(QTimerEvent *event)
{

}

void NotificationWidget::alphaAnimationFinished()
{
    if (mCloseAfterFinished) {
        close();
        qDebug() << "Close";
    }

    mCloseAfterFinished = false;
}
