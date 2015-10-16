#-------------------------------------------------
#
# Project created by QtCreator 2015-10-11T22:56:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SNF_tester
TEMPLATE = app

CONFIG += C++11
CONFIG += qt
QMAKE_LFLAGS += -fopenmp

SOURCES += gui/snf_tester_main.cpp \
    classes/snf_tester/snf_tester.cpp \
    gui/snf_tester_gui.cpp

HEADERS += classes/snf_tester/snf_tester.h \
          gui/snf_tester_gui.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/ -lSNF_lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/ -lSNF_libd
else:unix: LIBS += -L$$PWD/libs/ -lSNF_lib

INCLUDEPATH += $$PWD/libs
DEPENDPATH += $$PWD/libs

FORMS += \
    gui/snf_tester_gui.ui
