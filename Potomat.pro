#-------------------------------------------------
#
# Project created by QtCreator 2019-06-15T13:19:05
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Potomat
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        src/main.cpp \
        src/window/mainwindow.cpp \
    src/util/pomodoro.cpp \
    src/widget/swtabbar.cpp \
    src/util/configuration.cpp \
    src/widget/timerprogresswidget.cpp \
    src/widget/timelabelwidget.cpp \
    src/widget/swtabwidget.cpp \
    src/widget/notificationwidget.cpp

HEADERS += \
        src/window/mainwindow.h \
    src/util/pomodoro.h \
    src/widget/swtabbar.h \
    src/util/configuration.h \
    src/widget/timerprogresswidget.h \
    src/widget/timelabelwidget.h \
    src/widget/swtabwidget.h \
    src/widget/notificationwidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc

INCLUDEPATH += src

FORMS += \
    src/ui/mainwindow.ui \
    src/widget/notificationwidget.ui

RC_ICONS = arts/icon.ico
