#-------------------------------------------------
#
# Project created by QtCreator 2016-12-09T11:10:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Enlighten_Me
TEMPLATE = app


SOURCES += main.cpp\
        skeleton.cpp \
    qlwi_group.cpp \
    qlwi_user.cpp \
    manager_group.cpp \
    group.cpp \
    user.cpp \
    thread_console.cpp \
    manager_console.cpp

HEADERS  += skeleton.h \
    helper_macro.h \
    qlwi_group.h \
    qlwi_user.h \
    manager_group.h \
    group.h \
    user.h \
    helper_settings.h \
    thread_console.h \
    manager_console.h

FORMS    += skeleton.ui
