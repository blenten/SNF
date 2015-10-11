#-------------------------------------------------
#
# Project created by QtCreator 2015-10-11T22:56:38
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = SNF_tester
CONFIG   += console
CONFIG   -= app_bundle

CONFIG += C++11
CONFIG += qt
QMAKE_LFLAGS += -fopenmp

TEMPLATE = app


SOURCES += classes/snf_tester/snf_tester.cpp\
    classes/snf_tester/main_tester.cpp

HEADERS += \
    classes/snf_tester/snf_tester.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/ -lSNF_lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/ -lSNF_libd
else:unix: LIBS += -L$$PWD/libs/ -lSNF_lib

INCLUDEPATH += $$PWD/libs
DEPENDPATH += $$PWD/libs
