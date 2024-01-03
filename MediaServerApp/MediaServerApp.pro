QT += quick widgets
CONFIG += c++17
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
LIBS += -lQtSystemd

SOURCES += \
    ViewModel/MainWindow.cpp \
    ViewModel/SambaConfig.cpp \
    ViewModel/SambaConfigExternalDevice1.cpp \
    ViewModel/SambaConfigExternalDevice2.cpp \
    ViewModel/SambaConfigExternalDevice3.cpp \
    ViewModel/SambaConfigLocal.cpp \
    ViewModel/SambaConfigGlobal.cpp \
    ViewModel/FtpConfig.cpp \
    ViewModel/MassStorage.cpp \
    ViewModel/MultimediaConfig.cpp \
    ViewModel/ScreenSaver.cpp \
    ViewModel/NapiManager.cpp \
    ViewModel/SettingsScreenSaver.cpp \
    ViewModel/SettingsPackages.cpp \
    ViewModel/AlarmConfig.cpp \
    ViewModel/SettingsStatus.cpp \
    Bluetoothctl.cpp \
    ScreenSaverManager.cpp \
    start.cpp


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
    ViewModel/MainWindow.h \
    ViewModel/SambaConfig.h \
    ViewModel/FtpConfig.h \
    ViewModel/MassStorage.h \
    ViewModel/MultimediaConfig.h \
    ViewModel/ScreenSaver.h \
    ViewModel/NapiManager.h \
    ViewModel/SettingsScreenSaver.h \
    ViewModel/SettingsPackages.h \
    ViewModel/AlarmConfig.h \
    ViewModel/SettingsStatus.h \
    Bluetoothctl.h \
    ScreenSaverManager.h

FORMS +=

