#include "timerdial.h"
#include <QPainter>
#include <QResizeEvent>

TimerDial::TimerDial(QWidget *parent) : QWidget(parent)
{
    mBGPen.setColor("#858c99");
    mBGPen.setWidth(2);

    mFillPen.setColor("#ff4e4d");
    mFillPen.setWidth(10);
    mFillPen.setCapStyle(Qt::RoundCap);
}

void TimerDial::setPercent(float percent) {
    mPercent = percent;
    update();
}

float TimerDial::getPercent()
{
    return mPercent;
}

void TimerDial::setFillColor(QColor color)
{
    mFillPen.setColor(color);
}

void TimerDial::resizeEvent(QResizeEvent *event) {
    int width = event->size().width();
    int height = event->size().height();

    int wh = qMin(width, height);
    int paddingL = (width/2) - (wh/2);
    int paddingT = (height/2) - (wh/2);

    mRect.setLeft(paddingL+5);
    mRect.setTop(paddingT+5);
    mRect.setWidth(wh-10);
    mRect.setHeight(wh-10);
}

void TimerDial::paintEvent(QPaintEvent *event) {
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(mBGPen);
    painter.drawArc(mRect, startAngle, fullAngle);

    int spanAngle = (mPercent*360)*16;

    painter.setPen(mFillPen);
    painter.drawArc(mRect, startAngle, spanAngle);

    painter.end();
}
