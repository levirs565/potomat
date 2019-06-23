#include "swtabbar.h"
#include <QDebug>

SWTabBar::SWTabBar(QTabWidget *tabWidget)
    : QTabBar(),
      mTabWidget(tabWidget)
{

}

QSize SWTabBar::tabSizeHint(int index) const
{

    QSize sz = QTabBar::tabSizeHint(index);
    int w = (mTabWidget->width() / count()) - 1;
    return QSize(w, sz.height());
}
