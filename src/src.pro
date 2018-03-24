TARGET = snf
TEMPLATE = lib

INCLUDEPATH += $$PWD
include(src.pri)

SOURCES += \
    exceptions/invalidfunctionexception.cpp \
    snf_minimizer/snf_minimizer.cpp \
    snf_parser/expandedformparser.cpp \
    snf_parser/parser.cpp \
    snf_parser/shortformparser.cpp \
    snf_parser/snf_parserfacade.cpp \
    types/types.cpp \
    operand.cpp \
    qmm/qm_operand.cpp \
    qmm/qm_minimizer.cpp
