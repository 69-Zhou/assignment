#-------------------------------------------------
#
# Project created by QtCreator 2013-08-22T22:46:33
#
#-------------------------------------------------

QT       += core gui multimedia

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TowerDefense
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    towerposition.cpp \
    tower.cpp \
    waypoint.cpp \
    enemy.cpp \
    bullet.cpp \
    dialog.cpp \
    checkpoint.cpp \
    tower1.cpp \
    enemyson1.cpp \
    bullet1.cpp \
    tower2.cpp \
    enemyson2.cpp

HEADERS  += mainwindow.h \
    towerposition.h \
    tower.h \
    waypoint.h \
    utility.h \
    enemy.h \
    bullet.h \
    dialog.h \
    checkpoint.h \
    tower1.h \
    enemyson1.h \
    bullet1.h \
    tower2.h \
    enemyson2.h

FORMS    += mainwindow.ui \
    dialog.ui \
    checkpoint.ui

RESOURCES += \
    resource.qrc

RC_ICONS = timg.ico

DISTFILES +=

CONFIG += resources_big
