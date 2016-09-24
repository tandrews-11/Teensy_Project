#-------------------------------------------------
#
# Project created by QtCreator 2016-09-18T17:28:43
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TeensyProject
TEMPLATE = app
#CONFIG += install_ok


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RC_FILE = myapp.rc

#LIBS           = -C../plugins -lpnp_basictools
#LIBS           = -C../plugins -lpnp_extrafilters


