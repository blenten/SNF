#-------------------------------------------------
#
# Project created by QtCreator 2016-02-18T01:29:04
#
#-------------------------------------------------

QT += testlib
QT += core gui

CONFIG += qt warn_on depend_includepath testcase

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include (../../src/src.pri)
LIBS += -L../../src -lsnf

TEMPLATE = app

SOURCES += tst_qmm.cpp
