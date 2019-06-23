#ifndef ABOUTVIEW_H
#define ABOUTVIEW_H

#include <QWidget>
#include <QLabel>

class AboutView : public QLabel
{
    Q_OBJECT
public:
    explicit AboutView(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // ABOUTVIEW_H
