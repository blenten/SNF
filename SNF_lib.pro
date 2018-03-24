#-------------------------------------------------
#
# Project created by QtCreator 2015-10-11T22:33:32
#
#-------------------------------------------------

QT       -= gui

CONFIG += C++11

TARGET = SNF_lib
TEMPLATE = lib

DEFINES += SNF_LIB_LIBRARY
DEFINES += SNF_version=\\"2.0\\"

SOURCES += \
    classes/exceptions/invalidfunctionexception.cpp \
    classes/snf_minimizer/snf_minimizer.cpp \
    classes/snf_parser/expandedformparser.cpp \
    classes/snf_parser/parser.cpp \
    classes/snf_parser/shortformparser.cpp \
    classes/snf_parser/snf_parserfacade.cpp \
    classes/types/types.cpp \
    classes/operand.cpp \
    classes/qmm/qm_operand.cpp \
    classes/qmm/qm_minimizer.cpp


HEADERS += \
    classes/exceptions/invalidfunctionexception.h \
    classes/snf_minimizer/snf_minimizer.h \
    classes/snf_parser/expandedformparser.h \
    classes/snf_parser/parser.h \
    classes/snf_parser/shortformparser.h \
    classes/snf_parser/snf_parserfacade.h \
    classes/types/types.h \
    classes/lvar.h \
    classes/operand.h \
    classes/qmm/qm_operand.h \
    classes/qmm/qm_minimizer.h


unix {
    target.path = /usr/lib
    INSTALLS += target
}
