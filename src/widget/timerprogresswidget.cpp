#include "timerprogresswidget.h"
#include <QPainter>
#include <QResizeEvent>

TimerProgressWidget::TimerProgressWidget(QWidget *parent)
    : QWidget(parent),
      mType(Dial),
      mRound(Pomodoro::Work)
{
    mBGPen.setColor("#ffffff");
    mBGPen.setWidth(2);

    mFillColorWork = mFillColorShortBreak = mFillColorLongBreak = "#ffffff";

    mFillPen.setWidth(10);
    mFillPen.setCapStyle(Qt::RoundCap);

    updateFillColor();
}

void TimerProgressWidget::setPercent(float percent) {
    mPercent = percent;
    update();
}

float TimerProgressWidget::getPercent()
{
    return mPercent;
}

void TimerProgressWidget::setRound(Pomodoro::Round round)
{
    mRound = round;
    updateFillColor();
}

void TimerProgressWidget::setType(TimerProgressWidget::Type type)
{
    mType = type;
    update();
}

void TimerProgressWidget::setBackgroundColor(QColor color)
{
    mBGPen.setColor(color);
    update();
}

QColor TimerProgressWidget::getBackgroundColor()
{
    return mBGPen.color();
}

void TimerProgressWidget::setFillColorWork(QColor color)
{
    mFillColorWork = color;
    updateFillColor();
}

QColor TimerProgressWidget::getFillColorWork()
{
    return mFillColorWork;
}

void TimerProgressWidget::setFillColorShortBreak(QColor color)
{
    mFillColorShortBreak = color;
    updateFillColor();
}

QColor TimerProgressWidget::getFillColorShortBreak()
{
    return mFillColorShortBreak;
}

void TimerProgressWidget::setFillColorLongBreak(QColor color)
{
    mFillColorShortBreak = color;
    updateFillColor();
}

QColor TimerProgressWidget::getFillColorLongBreak()
{
    return mFillColorLongBreak;
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
    event->accept();
}

void TimerProgressWidget::updateFillColor()
{
    QColor color;
    if (mRound == Pomodoro::Work)
        color = mFillColorWork;
    else if (mRound == Pomodoro::ShortBreak)
        color = mFillColorShortBreak;
    else
        color = mFillColorLongBreak;

    mFillPen.setColor(color);
    update();
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
    event->accept();
}
