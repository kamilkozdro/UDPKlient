#-------------------------------------------------
#
# Project created by QtCreator 2014-08-17T17:34:56
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UDPKlient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    udpclient.cpp

HEADERS  += mainwindow.h \
    udpclient.h

FORMS    += mainwindow.ui

