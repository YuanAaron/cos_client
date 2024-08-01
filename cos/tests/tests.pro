QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    ../cosbrowser/src/bend/dao/clouds/daocloudscos.cpp \
    ../cosbrowser/src/config/exceptions.cpp \
    ../cosbrowser/src/helper/filehelper.cpp \
    main.cpp \
    testcos/tst_testcos.cpp \
    testexceptions/tst_testexceptions.cpp \
    testfilehelper/tst_testfilehelper.cpp

INCLUDEPATH += $$PWD/../cosbrowser

THIRD_DIR = $$PWD/../..

win32:CONFIG(release, debug|release): LIBS += -L$$THIRD_DIR/third/cos/libs/x64/ -lcossdk
else:win32:CONFIG(debug, debug|release): LIBS += -L$$THIRD_DIR/third/cos/libs/x64/ -lcossdkd
else:unix: LIBS += -L$$THIRD_DIR/third/cos/libs/x64/ -lcossdk

win32:CONFIG(release, debug|release): LIBS += -L$$THIRD_DIR/third/cos/third_party/lib/x64/poco/ -lPocoFoundation
else:win32:CONFIG(debug, debug|release): LIBS += -L$$THIRD_DIR/third/cos/third_party/lib/x64/poco/ -lPocoFoundation
else:unix: LIBS += -L$$THIRD_DIR/third/cos/third_party/lib/x64/poco/ -lPocoFoundation

INCLUDEPATH += $$THIRD_DIR/third/cos/include \
            $$THIRD_DIR/third/cos/third_party/include
DEPENDPATH += $$THIRD_DIR/third/cos/include \
            $$THIRD_DIR/third/cos/third_party/include

HEADERS += \
    testcos/tst_testcos.h \
    testexceptions/tst_testexceptions.h \
    testfilehelper/tst_testfilehelper.h

RESOURCES += \
    resource.qrc
