#include "drawerview.h"

DrawerView::DrawerView(QWidget *parent)
    : QTabWidget(parent),
      configView(new ConfigurationView()),
      aboutView(new AboutView()),
      swTabBar(new SWTabBar(this))
{
    setTabBar(swTabBar);
    addTab(configView, "Timer");
    addTab(aboutView, "About");
}
