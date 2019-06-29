#include "swtabwidget.h"
#include "swtabbar.h"

SWTabWidget::SWTabWidget(QWidget *parent) : QTabWidget(parent)
{
    setTabBar(new SWTabBar(this));
}
