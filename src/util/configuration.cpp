#include "configuration.h"
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QDebug>

Configuration::Configuration(QObject *parent) : QObject(parent)
{
    QString configLoc = QStandardPaths::locate(QStandardPaths::AppDataLocation,
                                               "config.json");

    if (configLoc.isEmpty()) {
        configLoc =
                QStandardPaths::standardLocations(QStandardPaths::AppDataLocation)[0] +
                "/config.json";
    }

    mConfigLocation = configLoc;

    load();
}

Configuration::~Configuration()
{
    save();
}

QVariant Configuration::getConfig(QString name)
{
    return mData[name].toVariant();
}

void Configuration::setConfig(QString name, QVariant value)
{
    mData[name] = QJsonValue::fromVariant(value);
}

void Configuration::load()
{
    qDebug() << "Loading configuration from" << mConfigLocation;
    QFile fl(mConfigLocation);

    if (fl.exists() && fl.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QByteArray raw = fl.readAll();

        QJsonParseError *error = nullptr;
        QJsonDocument document = QJsonDocument::fromJson(raw, error);

        if (!error) {
            if (document.isObject()) {
                mData = document.object();
            } else {
                qWarning() << "config.json value is not an object";
            }
        } else
            qWarning() << "read parse config.json with message " << error->errorString();


        fl.close();
    }
}

void Configuration::save()
{
    qDebug() << "Saving configuration to" << mConfigLocation;
    QFile fl(mConfigLocation);

    makeDir(mConfigLocation);

    if (fl.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QJsonDocument document(mData);
        QByteArray raw = document.toJson();

        fl.write(raw, raw.size());

        fl.close();
    } else {
        qWarning() << "Could not save configuration to" << mConfigLocation;
    }
}

void Configuration::makeDir(QString file)
{
    int index = file.lastIndexOf('/');
    QString dir = file.left(index);
    QDir().mkdir(dir);
}
