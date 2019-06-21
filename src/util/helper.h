#ifndef HELPER_H
#define HELPER_H
#include <QObject>

void setConnection(QObject* sender, const char* signal, QObject* receiver,
                   const char* slot);

#endif // HELPER_H
