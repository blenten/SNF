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
    ../../classes/qmm/qm_operand.cpp \
    ../../classes/snf_parser/snf_parserfacade.cpp \
    ../../classes/snf_parser/expandedformparser.cpp \
    ../../classes/snf_parser/parser.cpp \
    ../../classes/snf_parser/shortformparser.cpp \
    ../../classes/Types/types.cpp \
    ../../classes/Exceptions/invalidfunctionexception.cpp

HEADERS += \
    ../../classes/qmm/qm_minimizer.h \
    ../../classes/qmm/qm_operand.h \
    ../../classes/snf_parser/snf_parserfacade.h \
    ../../classes/snf_parser/expandedformparser.h \
    ../../classes/snf_parser/parser.h \
    ../../classes/snf_parser/shortformparser.h \
    ../../classes/Types/types.h \
    ../../classes/Exceptions/invalidfunctionexception.h
