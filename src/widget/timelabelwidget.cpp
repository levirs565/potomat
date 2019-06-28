#include "timelabelwidget.h"

TimeLabelWidget::TimeLabelWidget(QWidget *parent) : QLabel(parent)
{

}

const QChar TimeLabelWidget::zeroChar = QChar('0');
const QString TimeLabelWidget::formatArg = QString("%1:00");

void TimeLabelWidget::setMinute(int minute)
{
    setText(formatArg.arg(minute, 2, 10, zeroChar));
}
