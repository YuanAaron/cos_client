QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    src/bend/dao/daobucket.cpp \
    src/bend/dao/daologininfo.cpp \
    src/bend/manager/managerbucket.cpp \
    src/bend/manager/managerdb.cpp \
    src/bend/models/mybucket.cpp \
    src/fend/uicommon/breadwidget.cpp \
    src/fend/uicommon/mylineedit.cpp \
    src/fend/uicommon/pagewidget.cpp \
    src/fend/uidelegate/bucketdelegate.cpp \
    src/fend/uilogin/logindialog.cpp \
    src/fend/uimain/bucketswidget.cpp \
    src/fend/uimain/objectswidget.cpp \
    src/fend/uimain/toolbarwidget.cpp \
    src/fend/uimain/uimain.cpp \
    src/helper/dbsqlite.cpp \
    src/helper/filehelper.cpp

HEADERS += \
    src/bend/dao/daobucket.h \
    src/bend/dao/daologininfo.h \
    src/bend/manager/managerbucket.h \
    src/bend/manager/managerdb.h \
    src/bend/models/logininfo.h \
    src/bend/models/mybucket.h \
    src/config/config.h \
    src/fend/uicommon/breadwidget.h \
    src/fend/uicommon/mylineedit.h \
    src/fend/uicommon/pagewidget.h \
    src/fend/uidelegate/bucketdelegate.h \
    src/fend/uilogin/logindialog.h \
    src/fend/uimain/bucketswidget.h \
    src/fend/uimain/objectswidget.h \
    src/fend/uimain/toolbarwidget.h \
    src/fend/uimain/uimain.h \
    src/helper/dbsqlite.h \
    src/helper/filehelper.h

FORMS += \
    src/fend/uicommon/breadwidget.ui \
    src/fend/uicommon/pagewidget.ui \
    src/fend/uilogin/logindialog.ui \
    src/fend/uimain/bucketswidget.ui \
    src/fend/uimain/objectswidget.ui \
    src/fend/uimain/toolbarwidget.ui \
    src/fend/uimain/uimain.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
