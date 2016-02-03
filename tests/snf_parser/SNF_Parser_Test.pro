#-------------------------------------------------
#
# Project created by QtCreator 2016-02-03T02:46:35
#
#-------------------------------------------------

QT       += core

QT       -= gui

CONFIG +=C++11

TARGET = SNF_Parser_Test
CONFIG   += console
CONFIG   -= app_bundle

SOURCES += \
     ../../classes/Exceptions/invalidfunctionexception.cpp \
     ../../classes/snf_minimizer/snf_minimizer.cpp \
     ../../classes/Types/types.cpp \
     ../../classes/snf_parser/shortformparser.cpp \
     ../../classes/snf_parser/expandedformparser.cpp \
     ../../classes/snf_parser/parser.cpp \
     ../../classes/snf_parser/snf_parserfacade.cpp \
     ../../classes/operand.cpp \

HEADERS  += \
     ../../classes/Exceptions/invalidfunctionexception.h \
     ../../classes/snf_minimizer/snf_minimizer.h \
     ../../classes/lvar.h \
     ../../classes/Types/types.h \
     ../../classes/snf_parser/shortformparser.h \
     ../../classes/snf_parser/expandedformparser.h \
     ../../classes/snf_parser/parser.h \
     ../../classes/snf_parser/snf_parserfacade.h \
     ../../classes/operand.h \

TEMPLATE = app


SOURCES += main.cpp
