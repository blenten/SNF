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
CONFIG += qt
QMAKE_LFLAGS += -fopenmp

SOURCES += main.cpp\
        snf_gui.cpp \
    classes/Exceptions/invalidfunctionexception.cpp \
    classes/snf_minimizer/snf_minimizer.cpp \
    log.cpp \
    classes/localizator/localizator.cpp \
    classes/Types/types.cpp \
    classes/snf_parser/shortformparser.cpp \
    classes/snf_parser/expandedformparser.cpp \
    classes/snf_parser/parser.cpp \
    classes/snf_parser/snf_parserdecorator.cpp \
    classes/snf_tester/snf_tester.cpp

HEADERS  += snf_gui.h \
    classes/Exceptions/invalidfunctionexception.h \
    classes/snf_minimizer/snf_minimizer.h \
    classes/lvar.h \
    log.h \
    classes/localizator/localizator.h \
    classes/Types/types.h \
    classes/snf_parser/shortformparser.h \
    classes/snf_parser/expandedformparser.h \
    classes/snf_parser/parser.h \
    classes/snf_parser/snf_parserdecorator.h \
    classes/snf_tester/snf_tester.h

FORMS    += snf_gui.ui \
    log.ui

DISTFILES +=

RESOURCES += \
    localization/locale.qrc
