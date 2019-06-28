#ifndef TIMERLABELWIDGET_H
#define TIMERLABELWIDGET_H

#include <QWidget>
#include <QLabel>

class TimeLabelWidget : public QLabel
{
    Q_OBJECT
public:
    explicit TimeLabelWidget(QWidget *parent = nullptr);

private:
    static const QChar zeroChar;
    static const QString formatArg;

signals:

public slots:
    void setMinute(int minute);

};

#endif // TIMERLABELWIDGET_H
