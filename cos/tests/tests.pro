QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    testcos/tst_testcos.cpp \
    testexceptions/tst_testexceptions.cpp \
    testfilehelper/tst_testfilehelper.cpp

INCLUDEPATH += $$PWD/../cosbrowser

THIRD_DIR = $$PWD/../..

include(../cosbrowser/cosbrowser.pri)

HEADERS += \
    testcos/tst_testcos.h \
    testexceptions/tst_testexceptions.h \
    testfilehelper/tst_testfilehelper.h

RESOURCES += \
    resource.qrc
