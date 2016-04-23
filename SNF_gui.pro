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
DEFINES += SNF_version=\\\"2.0\\\"

SOURCES += main.cpp\
    gui/log.cpp \
    gui/help.cpp \
    classes/localizator/localizator.cpp \
    gui/snfg.cpp

HEADERS  +=  \
    gui/log.h \
    gui/help.h \
    classes/localizator/localizator.h \
    gui/snfg.h

FORMS    += \
    gui/log.ui \
    gui/help.ui \
    gui/snfg.ui

DISTFILES +=

RESOURCES += \
    localization/locale.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/ -lSNF_lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/ -lSNF_libd
else:unix: LIBS += -L$$PWD/libs/ -lSNF_lib

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/
