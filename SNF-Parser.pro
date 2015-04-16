#-------------------------------------------------
#
# Project created by QtCreator 2015-04-12T15:26:14
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = SNF-Parser
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    snf_minimizer/snf_minimizer.cpp \
    snf_parser/snf_parser.cpp

HEADERS += \
    snf_minimizer/snf_minimizer.h \
    snf_parser/snf_parser.h \
    lvar.h
