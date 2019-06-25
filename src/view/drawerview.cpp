#include "drawerview.h"

DrawerView::DrawerView(QWidget *parent)
    : QTabWidget(parent),
      configView(new ConfigurationView()),
      aboutView(new AboutView()),
      swTabBar(new SWTabBar(this))
{
    setTabBar(swTabBar);
    addTab(configView, QString::fromWCharArray(L"\ue192"));
    addTab(aboutView, QString::fromWCharArray(L"\ue88e"));
}
