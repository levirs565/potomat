#ifndef DRAWERVIEW_H
#define DRAWERVIEW_H

#include <QWidget>
#include <QTabWidget>
#include "configurationview.h"
#include "aboutview.h"
#include "../widget/swtabbar.h"

class DrawerView : public QTabWidget
{
    Q_OBJECT
public:
    explicit DrawerView(QWidget *parent = nullptr);

    ConfigurationView *configView;
    AboutView *aboutView;
    SWTabBar *swTabBar;

signals:

public slots:
};

#endif // DRAWERVIEW_H
