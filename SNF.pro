#-------------------------------------------------
#
# Project created by QtCreator 2015-05-30T20:45:12
#
#-------------------------------------------------


#debug project

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SNF_gui
TEMPLATE = app

CONFIG += C++11
CONFIG += qt

SOURCES += main.cpp \
     gui/snf_gui.cpp \
     classes/Exceptions/invalidfunctionexception.cpp \
     classes/snf_minimizer/snf_minimizer.cpp \
     gui/log.cpp \
     classes/localizator/localizator.cpp \
     classes/Types/types.cpp \
     classes/snf_parser/shortformparser.cpp \
     classes/snf_parser/expandedformparser.cpp \
     classes/snf_parser/parser.cpp \
     classes/snf_parser/snf_parserdecorator.cpp

HEADERS  += gui/snf_gui.h \
     classes/Exceptions/invalidfunctionexception.h \
     classes/snf_minimizer/snf_minimizer.h \
     classes/lvar.h \
     gui/log.h \
     classes/localizator/localizator.h \
     classes/Types/types.h \
     classes/snf_parser/shortformparser.h \
     classes/snf_parser/expandedformparser.h \
     classes/snf_parser/parser.h \
     classes/snf_parser/snf_parserdecorator.h \

FORMS    += gui/snf_gui.ui \
    gui/log.ui

DISTFILES +=

RESOURCES += \
    localization/locale.qrc