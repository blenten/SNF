#-------------------------------------------------
#
# Project created by QtCreator 2016-02-18T01:29:04
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_qmmtest
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += C++11

TEMPLATE = app
DEFINES += SRCDIR=\\\"$$PWD/\\\"

SOURCES += \
    tst_qmm.cpp \
    ../../classes/qmm/qm_minimizer.cpp \
    ../../classes/qmm/qm_operand.cpp

HEADERS += \
    ../../classes/qmm/qm_minimizer.h \
    ../../classes/qmm/qm_operand.h
