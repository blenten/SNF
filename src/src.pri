CONFIG -= debug_and_release debug_and_release_target
QT += core

INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/exceptions/invalidfunctionexception.h \
    $$PWD/snf_minimizer/snf_minimizer.h \
    $$PWD/snf_parser/expandedformparser.h \
    $$PWD/snf_parser/parser.h \
    $$PWD/snf_parser/shortformparser.h \
    $$PWD/snf_parser/snf_parserfacade.h \
    $$PWD/types/types.h \
    $$PWD/lvar.h \
    $$PWD/operand.h \
    $$PWD/qmm/qm_operand.h \
    $$PWD/qmm/qm_minimizer.h
