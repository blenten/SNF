#-------------------------------------------------
#
# Project created by QtCreator 2015-05-30T20:45:12
#
#-------------------------------------------------

QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SNF_gui
TEMPLATE = app

CONFIG += C++11
QMAKE_LFLAGS += -fopenmp

SOURCES += main.cpp\
        snf_gui.cpp \
    classes/Exceptions/invalidfunctionexception.cpp \
    classes/snf_generator/snf_generator.cpp \
    classes/snf_minimizer/snf_minimizer.cpp \
    classes/snf_parser/snf_parser.cpp \
    log.cpp

HEADERS  += snf_gui.h \
    classes/Exceptions/invalidfunctionexception.h \
    classes/snf_generator/snf_generator.h \
    classes/snf_minimizer/snf_minimizer.h \
    classes/snf_parser/snf_parser.h \
    classes/lvar.h \
    log.h

FORMS    += snf_gui.ui \
    log.ui
