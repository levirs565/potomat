#include "aboutview.h"

AboutView::AboutView(QWidget *parent) : QLabel(parent)
{
    setMargin(11);
    setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    setText("Potomat is lightweight Pomodoro timer app.");
}
