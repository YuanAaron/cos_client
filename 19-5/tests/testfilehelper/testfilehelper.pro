QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_testfilehelper.cpp \
    ../../cosbrowser/src/helper/filehelper.cpp

INCLUDEPATH += $$PWD/../../cosbrowser

RESOURCES += \
    resource.qrc

HEADERS += \
    ../../cosbrowser/src/helper/filehelper.h
