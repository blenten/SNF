TARGET = SNF
TEMPLATE = app

QT += gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += $$PWD

include(../src/src.pri)
LIBS += -L../src -lsnf

HEADERS += \
    gui.h \
    snf_tester/snf_tester.h

SOURCES += main.cpp \
    gui.cpp \
    snf_tester/snf_tester.cpp

FORMS += \
    gui.ui
