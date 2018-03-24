TARGET = SNF
TEMPLATE = app

QT += gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += $$PWD

include(../src/src.pri)
LIBS += -L../src -lsnf

HEADERS += \
    log.h \
    help.h \
    localizator/localizator.h \
    snfg.h

SOURCES +=  main.cpp \
    log.cpp \
    help.cpp \
    localizator/localizator.cpp \
    snfg.cpp

FORMS += \
    log.ui \
    help.ui \
    snfg.ui

RESOURCES += \
    ../localization/locale.qrc
