#include "drawerview.h"

DrawerView::DrawerView(QWidget *parent)
    : QTabWidget(parent),
      configView(new ConfigurationView()),
      aboutView(new AboutView())
{
    addTab(configView, "Timer");
    addTab(aboutView, "About");
}
