#-------------------------------------------------
#
# Project created by QtCreator 2016-02-18T01:29:04
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_facadetest
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += C++11

TEMPLATE = app
DEFINES += SRCDIR=\\\"$$PWD/\\\"

SOURCES += \
    tst_qmparser.cpp \
    ../../classes/snf_parser/parser.cpp \
    ../../classes/snf_parser/shortformparser.cpp \
    ../../classes/snf_parser/expandedformparser.cpp \
    ../../classes/snf_parser/snf_parserfacade.cpp \
    ../../classes/qmm/qm_operand.cpp \
    ../../classes/Types/types.cpp \
     ../../classes/Exceptions/invalidfunctionexception.cpp \
    ../../classes/operand.cpp

HEADERS += \
    ../../classes/snf_parser/parser.h \
    ../../classes/snf_parser/shortformparser.h \
    ../../classes/snf_parser/expandedformparser.h \
    ../../classes/snf_parser/snf_parserfacade.h \
    ../../classes/qmm/qm_operand.h \
    ../../classes/Types/types.h \
     ../../classes/Exceptions/invalidfunctionexception.h \
    ../../classes/operand.h
