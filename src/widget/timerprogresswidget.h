#ifndef TIMERDIAL_H
#define TIMERDIAL_H

#include <QWidget>
#include <QPen>
#include "../util/pomodoro.h"

class TimerProgressWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor background READ getBackgroundColor WRITE setBackgroundColor
               DESIGNABLE true)
    Q_PROPERTY(QColor fillColorWork READ getFillColorWork WRITE setFillColorWork
               DESIGNABLE true)
    Q_PROPERTY(QColor fillColorShortBreak READ getFillColorShortBreak WRITE setFillColorShortBreak
               DESIGNABLE true)
    Q_PROPERTY(QColor fillColorLongBreak READ getFillColorLongBreak WRITE setFillColorLongBreak
               DESIGNABLE true)
public:
    enum Type {
        Dial,
        Horizontal
    };

    explicit TimerProgressWidget(QWidget *parent = nullptr);

    void setPercent(float percent);
    float getPercent();

    void setRound(Pomodoro::Round round);
    void setType(Type type);

    void setBackgroundColor(QColor color);
    QColor getBackgroundColor();

    void setFillColorWork(QColor color);
    QColor getFillColorWork();

    void setFillColorShortBreak(QColor color);
    QColor getFillColorShortBreak();

    void setFillColorLongBreak(QColor color);
    QColor getFillColorLongBreak();

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private:
    float mPercent;
    Type mType;
    QPen mBGPen;
    QPen mFillPen;
    QRect mRect;
    QRect mOriginRect;
    Pomodoro::Round mRound;

    QColor mFillColorWork;
    QColor mFillColorShortBreak;
    QColor mFillColorLongBreak;

    void updateFillColor();

    static const int startAngle = 90*16;
    static const int fullAngle = 360*16;
signals:

public slots:
};

#endif // TIMERDIAL_H
