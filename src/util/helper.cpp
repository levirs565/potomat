#include "helper.h"

void setConnection(QObject *sender, const char *signal, QObject *receiver, const char *slot)
{
    sender->disconnect(signal);

    if (slot != nullptr) {
        sender->connect(sender, signal, receiver, slot);
    }
}
