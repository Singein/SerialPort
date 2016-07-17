#-------------------------------------------------
#
# Project created by QtCreator 2016-03-09T10:29:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MySeriaPort
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    form.cpp \
    about.cpp

HEADERS  += mainwindow.h \
    form.h \
    about.h

FORMS    += mainwindow.ui \
    form.ui \
    about.ui
QT += serialport

RESOURCES += \
    src.qrc

RC_ICONS = myico.ico

