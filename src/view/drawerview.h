#ifndef DRAWERVIEW_H
#define DRAWERVIEW_H

#include <QWidget>
#include <QTabWidget>
#include "configurationview.h"
#include "aboutview.h"

class DrawerView : public QTabWidget
{
    Q_OBJECT
public:
    explicit DrawerView(QWidget *parent = nullptr);

    ConfigurationView *configView;
    AboutView *aboutView;

signals:

public slots:
};

#endif // DRAWERVIEW_H
