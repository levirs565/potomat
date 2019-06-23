#ifndef SWTABBAR_H
#define SWTABBAR_H

#include <QWidget>
#include <QTabBar>
#include <QTabWidget>

class SWTabBar : public QTabBar
{
    Q_OBJECT
public:
    explicit SWTabBar(QTabWidget *tabWidget = nullptr);

     QSize tabSizeHint(int index) const override;

private:
     QTabWidget *mTabWidget;

signals:

public slots:
};

#endif // SWTABBAR_H
