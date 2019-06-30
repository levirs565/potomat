#include "timerprogresswidget.h"
#include <QPainter>
#include <QResizeEvent>

TimerProgressWidget::TimerProgressWidget(QWidget *parent)
    : QWidget(parent),
      mType(Dial)
{
    mBGPen.setColor("#858c99");
    mBGPen.setWidth(2);

    mFillPen.setColor("#ff4e4d");
    mFillPen.setWidth(10);
    mFillPen.setCapStyle(Qt::RoundCap);
}

void TimerProgressWidget::setPercent(float percent) {
    mPercent = percent;
    update();
}

float TimerProgressWidget::getPercent()
{
    return mPercent;
}

void TimerProgressWidget::setFillColor(QColor color)
{
    mFillPen.setColor(color);
}

void TimerProgressWidget::setType(TimerProgressWidget::Type type)
{
    mType = type;
    update();
}

void TimerProgressWidget::resizeEvent(QResizeEvent *event) {
    int width = event->size().width();
    int height = event->size().height();

    int wh = qMin(width, height);
    int paddingL = (width/2) - (wh/2);
    int paddingT = (height/2) - (wh/2);

    mRect.setLeft(paddingL+5);
    mRect.setTop(paddingT+5);
    mRect.setWidth(wh-10);
    mRect.setHeight(wh-10);

    mOriginRect.setLeft(0);
    mOriginRect.setTop(0);
    mOriginRect.setWidth(width);
    mOriginRect.setHeight(height);
}

void TimerProgressWidget::paintEvent(QPaintEvent *event) {
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

//    painter.fillRect(rect(), Qt::red);

    if (mType == Dial) {
        painter.setPen(mBGPen);
        painter.drawArc(mRect, startAngle, fullAngle);

        int spanAngle = (mPercent*360)*16;

        painter.setPen(mFillPen);
        painter.drawArc(mRect, startAngle, spanAngle);
    } else {
        painter.fillRect(mOriginRect, mBGPen.brush());

        int hp = (mPercent * mOriginRect.width());

        painter.fillRect(0, 0, hp, mOriginRect.height(), mFillPen.brush());
    }

    painter.end();
}
