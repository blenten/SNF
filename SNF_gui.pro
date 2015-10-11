#-------------------------------------------------
#
# Project created by QtCreator 2015-05-30T20:45:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SNF_gui
TEMPLATE = app

CONFIG += C++11
CONFIG += qt


SOURCES += main.cpp\
        snf_gui.cpp \
    log.cpp \
    classes/localizator/localizator.cpp \

HEADERS  += snf_gui.h \
    log.h \
    classes/localizator/localizator.h \

FORMS    += snf_gui.ui \
    log.ui

DISTFILES +=

RESOURCES += \
    localization/locale.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/ -lSNF_lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/ -lSNF_libd
else:unix: LIBS += -L$$PWD/libs/ -lSNF_lib

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/
