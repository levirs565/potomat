#include "drawerview.h"

DrawerView::DrawerView(QWidget *parent)
    : QTabWidget(parent),
      configView(new ConfigurationView())
{
    addTab(configView, "Timer");
}
