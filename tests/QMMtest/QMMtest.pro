#-------------------------------------------------
#
# Project created by QtCreator 2016-02-18T01:29:04
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_kmmtest
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += C++11

TEMPLATE = app


SOURCES += \
    tst_qmm.cpp \
    ../../classes/qmm/qm_minimizer.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../classes/qmm/qm_minimizer.h
