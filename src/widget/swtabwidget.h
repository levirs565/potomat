#ifndef SWTABWIDGET_H
#define SWTABWIDGET_H

#include <QWidget>
#include <QTableWidget>

class SWTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit SWTabWidget(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // SWTABWIDGET_H
