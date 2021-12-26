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

INCLUDEPATH += ../MediaServerLib
LIBS += -L../MediaServerLib -lMediaServerLib

SOURCES += \
    src/ViewModel/mainwindow.cpp \
    src/ViewModel/sambaconfig.cpp \
    src/ViewModel/quotes.cpp \
    src/start.cpp \
    src/ViewModel/sambaconfigexternaldevice1.cpp \
    src/ViewModel/sambaconfigexternaldevice2.cpp \
    src/ViewModel/sambaconfigexternaldevice3.cpp \
    src/ViewModel/sambaconfiglocal.cpp \
    src/ViewModel/sambaconfigglobal.cpp \
    src/ViewModel/ftpconfig.cpp \
    src/bluetoothctl.cpp \
    src/ViewModel/massstorage.cpp \
    src/ViewModel/multimediaconfig.cpp \
    src/screensavermanager.cpp \
    src/ViewModel/screensaver.cpp \
    src/ViewModel/napimanager.cpp \
    src/ViewModel/settingsscreensaver.cpp \
    src/ViewModel/settingspackages.cpp

RESOURCES += resources/qml.qrc

TEMPLATE = app

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
target.path = /opt
INSTALLS += target

HEADERS += \
    src/ViewModel/mainwindow.h \
    src/ViewModel/sambaconfig.h \
    src/ViewModel/ftpconfig.h \
    src/bluetoothctl.h \
    src/ViewModel/massstorage.h \
    src/ViewModel/multimediaconfig.h \
    src/ViewModel/quotes.h \
    src/screensavermanager.h \
    src/ViewModel/screensaver.h \
    src/ViewModel/napimanager.h \
    src/ViewModel/settingsscreensaver.h \
    src/ViewModel/settingspackages.h

FORMS +=

