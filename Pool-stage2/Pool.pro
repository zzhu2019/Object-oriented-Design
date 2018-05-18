#-------------------------------------------------
#
# Project created by QtCreator 2018-04-01T02:52:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Pool
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    scenemanager.cpp \
    simpletable.cpp \
	simpleball.cpp \
	simplecreator.cpp \
	scenebuilder.cpp \
	creator.cpp \
    pockettable.cpp \
    pocket.cpp \
    compositeball.cpp

HEADERS += \
        mainwindow.h \
    util.h \
    scenemanager.h \
    graphic.h \
    table.h \
    ball.h \
    simpleball.h \
    simpletable.h \
    scenebuilder.h \
    creator.h \
    simplecreator.h \
    pockettable.h \
    pocket.h \
    compositeball.h

DISTFILES += \
    config.json \
    config_stage2.json

copyconfig.depends = ../Pool/config.json
copyconfig.commands = \
	$(COPY_FILE) \"$$shell_path($$PWD\\config.json)\" .

first.depends = all copyconfig
QMAKE_EXTRA_TARGETS += first copyconfig
