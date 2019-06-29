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
    int c = count();
    int w = (mTabWidget->width() / c);

    if (index < c - 1)
        w -= 1;

    return QSize(w, sz.height());
}
