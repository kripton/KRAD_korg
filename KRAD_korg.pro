#-------------------------------------------------
#
# Project created by QtCreator 2012-11-19T22:54:21
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = KRAD_korg
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    jackthread.cpp \
    application.cpp

HEADERS += \
    jackthread.h \
    application.h

LIBS += -ljack
