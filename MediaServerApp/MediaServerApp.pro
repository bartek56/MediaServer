QT += core qml quick widgets
CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
static {
    QT += svg
    QTPLUGIN += qtvirtualkeyboardplugin
}

SOURCES += \
    ViewModel/mainwindow.cpp \
    ViewModel/sambaconfig.cpp \
    start.cpp \
    ViewModel/sambaconfigexternaldevice1.cpp \
    ViewModel/sambaconfigexternaldevice2.cpp \
    ViewModel/sambaconfigexternaldevice3.cpp \
    ViewModel/sambaconfiglocal.cpp \
    ViewModel/sambaconfigglobal.cpp \
    ViewModel/ftpconfig.cpp \
    editsambaconfigfile.cpp \
    editftpconfigfile.cpp \
    ViewModel/settings.cpp \
    editwificonfigfile.cpp

RESOURCES += qml.qrc

TEMPLATE = app

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ViewModel/mainwindow.h \
    ViewModel/sambaconfig.h \
    ViewModel/ftpconfig.h \
    editsambaconfigfile.h \
    editftpconfigfile.h \
    ViewModel/settings.h \
    editwificonfigfile.h

FORMS +=





