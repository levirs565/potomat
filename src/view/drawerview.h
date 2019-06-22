#ifndef DRAWERVIEW_H
#define DRAWERVIEW_H

#include <QWidget>
#include <QTabWidget>
#include "configurationview.h"

class DrawerView : public QTabWidget
{
    Q_OBJECT
public:
    explicit DrawerView(QWidget *parent = nullptr);

    ConfigurationView *configView;

signals:

public slots:
};

#endif // DRAWERVIEW_H
