#ifndef TIMERDIAL_H
#define TIMERDIAL_H

#include <QWidget>
#include <QPen>

class TimerDial : public QWidget
{
    Q_OBJECT
public:
    explicit TimerDial(QWidget *parent = nullptr);

    void setPercent(float percent);
    float getPercent();

    void setFillColor(QColor color);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private:
    float mPercent;
    QPen mBGPen;
    QPen mFillPen;
    QRect mRect;

    static const int startAngle = 90*16;
    static const int fullAngle = 360*16;
signals:

public slots:
};

#endif // TIMERDIAL_H
