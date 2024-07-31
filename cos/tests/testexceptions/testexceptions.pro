QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_testexceptions.cpp \
    ../../cosbrowser/src/config/exceptions.cpp \
    ../../cosbrowser/src/helper/filehelper.cpp

INCLUDEPATH += $$PWD/../../cosbrowser
