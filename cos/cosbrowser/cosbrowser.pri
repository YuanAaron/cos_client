QT       += core gui sql concurrent

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
    $$PWD/src/bend/dao/clouds/daocloudscos.cpp \
    $$PWD/src/bend/dao/clouds/daocloudsmock.cpp \
    $$PWD/src/bend/dao/config/version.cpp \
    $$PWD/src/bend/dao/config/versioncmd.cpp \
    $$PWD/src/bend/dao/config/versionjson.cpp \
    $$PWD/src/bend/dao/dbs/daologininfosqlite.cpp \
    $$PWD/src/bend/dao/logs/basiclogger.cpp \
    $$PWD/src/bend/dao/logs/loggerqdebug.cpp \
    $$PWD/src/bend/gateway.cpp \
    $$PWD/src/bend/manager/managercloud.cpp \
    $$PWD/src/bend/manager/managerdb.cpp \
    $$PWD/src/config/exceptions.cpp \
    $$PWD/src/config/loggerproxy.cpp \
    $$PWD/src/fend/uicommon/basedialog.cpp \
    $$PWD/src/fend/uicommon/breadwidget.cpp \
    $$PWD/src/fend/uicommon/comboline.cpp \
    $$PWD/src/fend/uicommon/cosdialog.cpp \
    $$PWD/src/fend/uicommon/mylineedit.cpp \
    $$PWD/src/fend/uicommon/pagewidget.cpp \
    $$PWD/src/fend/uidelegate/bucketdelegate.cpp \
    $$PWD/src/fend/uilogin/logindialog.cpp \
    $$PWD/src/fend/uimain/bucketswidget.cpp \
    $$PWD/src/fend/uimain/objectswidget.cpp \
    $$PWD/src/fend/uimain/toolbarwidget.cpp \
    $$PWD/src/fend/uimain/uimain.cpp \
    $$PWD/src/helper/dbsqlite.cpp \
    $$PWD/src/helper/filehelper.cpp \
    $$PWD/src/middle/managerglobal.cpp \
    $$PWD/src/middle/managermodel.cpp \
    $$PWD/src/middle/signals/managersignals.cpp \
    $$PWD/src/plugins/managerplugin.cpp

HEADERS += \
    $$PWD/src/bend/dao/clouds/DaoClouds.h \
    $$PWD/src/bend/dao/clouds/daocloudscos.h \
    $$PWD/src/bend/dao/clouds/daocloudsmock.h \
    $$PWD/src/bend/dao/config/version.h \
    $$PWD/src/bend/dao/config/versioncmd.h \
    $$PWD/src/bend/dao/config/versionjson.h \
    $$PWD/src/bend/dao/dbs/daologininfo.h \
    $$PWD/src/bend/dao/dbs/daologininfosqlite.h \
    $$PWD/src/bend/dao/logs/basiclogger.h \
    $$PWD/src/bend/dao/logs/loggerqdebug.h \
    $$PWD/src/bend/gateway.h \
    $$PWD/src/bend/manager/managercloud.h \
    $$PWD/src/bend/manager/managerdb.h \
    $$PWD/src/config/api.h \
    $$PWD/src/config/errorcode.h \
    $$PWD/src/config/exceptions.h \
    $$PWD/src/config/global.h \
    $$PWD/src/config/loggerproxy.h \
    $$PWD/src/fend/uicommon/basedialog.h \
    $$PWD/src/fend/uicommon/breadwidget.h \
    $$PWD/src/fend/uicommon/comboline.h \
    $$PWD/src/fend/uicommon/cosdialog.h \
    $$PWD/src/fend/uicommon/mylineedit.h \
    $$PWD/src/fend/uicommon/pagewidget.h \
    $$PWD/src/fend/uidelegate/bucketdelegate.h \
    $$PWD/src/fend/uilogin/logindialog.h \
    $$PWD/src/fend/uimain/bucketswidget.h \
    $$PWD/src/fend/uimain/objectswidget.h \
    $$PWD/src/fend/uimain/toolbarwidget.h \
    $$PWD/src/fend/uimain/uimain.h \
    $$PWD/src/helper/dbsqlite.h \
    $$PWD/src/helper/filehelper.h \
    $$PWD/src/middle/managerglobal.h \
    $$PWD/src/middle/managermodel.h \
    $$PWD/src/middle/models/cloudmodels.h \
    $$PWD/src/middle/models/dbmodels.h \
    $$PWD/src/middle/signals/managersignals.h \
    $$PWD/src/plugins/managerplugin.h

FORMS += \
    $$PWD/src/fend/uicommon/basedialog.ui \
    $$PWD/src/fend/uicommon/breadwidget.ui \
    $$PWD/src/fend/uicommon/cosdialog.ui \
    $$PWD/src/fend/uicommon/pagewidget.ui \
    $$PWD/src/fend/uilogin/logindialog.ui \
    $$PWD/src/fend/uimain/bucketswidget.ui \
    $$PWD/src/fend/uimain/objectswidget.ui \
    $$PWD/src/fend/uimain/toolbarwidget.ui \
    $$PWD/src/fend/uimain/uimain.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

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
