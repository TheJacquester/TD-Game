#-------------------------------------------------
#
# Project created by QtCreator 2017-04-08T23:17:18
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = Legion_TD_V1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp \
    game.cpp \
    tower.cpp \
    tile.cpp \
    map.cpp \
    enemy.cpp \
    normaltower.cpp \
    frosttower.cpp \
    inteltower.cpp \
    ultitower.cpp \
    pathfinder.cpp \
    bullet.cpp \
    loadscreen.cpp \
    infopane.cpp \
    udpsocket.cpp \
    towerpane.cpp

HEADERS  += \
    game.h \
    tower.h \
    tile.h \
    map.h \
    enemy.h \
    normaltower.h \
    frosttower.h \
    inteltower.h \
    ultitower.h \
    pathfinder.h \
    bullet.h \
    loadscreen.h \
    infopane.h \
    udpsocket.h \
    towerpane.h

FORMS    +=

RESOURCES += \
    res.qrc

RC_ICONS = icon.ico
