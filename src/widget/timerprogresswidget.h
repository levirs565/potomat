#ifndef TIMERDIAL_H
#define TIMERDIAL_H

#include <QWidget>
#include <QPen>

class TimerProgressWidget : public QWidget
{
    Q_OBJECT
public:
    enum Type {
        Dial,
        Horizontal
    };

    explicit TimerProgressWidget(QWidget *parent = nullptr);

    void setPercent(float percent);
    float getPercent();

    void setFillColor(QColor color);
    void setType(Type type);

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

    static const int startAngle = 90*16;
    static const int fullAngle = 360*16;
signals:

public slots:
};

#endif // TIMERDIAL_H
