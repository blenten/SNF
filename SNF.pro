#-------------------------------------------------
#
# Project created by QtCreator 2015-05-30T20:45:12
#
#-------------------------------------------------


#debug project

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SNFG
TEMPLATE = app

CONFIG += C++11
CONFIG += qt
DEFINES += SNF_version=\\\"2.0\\\"

SOURCES += main.cpp \
     gui/log.cpp \
     gui/help.cpp \
     classes/Exceptions/invalidfunctionexception.cpp \
     classes/snf_minimizer/snf_minimizer.cpp \
     classes/localizator/localizator.cpp \
     classes/types/types.cpp \
     classes/snf_parser/shortformparser.cpp \
     classes/snf_parser/expandedformparser.cpp \
     classes/snf_parser/parser.cpp \
     classes/snf_parser/snf_parserfacade.cpp \
     classes/operand.cpp \
     classes/qmm/qm_operand.cpp \
     classes/qmm/qm_minimizer.cpp \
     gui/snfg.cpp

HEADERS  += \
     gui/log.h \
     gui/help.h \
     classes/Exceptions/invalidfunctionexception.h \
     classes/snf_minimizer/snf_minimizer.h \
     classes/lvar.h \
     classes/localizator/localizator.h \
     classes/types/types.h \
     classes/snf_parser/shortformparser.h \
     classes/snf_parser/expandedformparser.h \
     classes/snf_parser/parser.h \
     classes/snf_parser/snf_parserfacade.h \
     classes/operand.h \
     classes/qmm/qm_operand.h \
     classes/qmm/qm_minimizer.h \
     gui/snfg.h

FORMS    += \
    gui/log.ui \
    gui/help.ui \
    gui/snfg.ui

DISTFILES +=

RESOURCES += \
    localization/locale.qrc
