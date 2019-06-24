#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QObject>
#include <QJsonObject>

class Configuration : public QObject
{
    Q_OBJECT
public:
    explicit Configuration(QObject *parent = nullptr);
    ~Configuration();

    QVariant getConfig(QString name);
    void setConfig(QString name, QVariant value);

private:

    void load();
    void save();

    QString mConfigLocation;
    QJsonObject mData;

    static void makeDir(QString file);

signals:

public slots:
};

#endif // CONFIGURATION_H
