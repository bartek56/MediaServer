QT += core qml quick widgets dbus
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
    src/ViewModel/MainWindow.cpp \
    src/ViewModel/SambaConfig.cpp \
    src/ViewModel/Quotes.cpp \
    src/start.cpp \
    src/ViewModel/SambaConfigExternalDevice1.cpp \
    src/ViewModel/SambaConfigExternalDevice2.cpp \
    src/ViewModel/SambaConfigExternalDevice3.cpp \
    src/ViewModel/SambaConfigLocal.cpp \
    src/ViewModel/SambaConfigGlobal.cpp \
    src/ViewModel/FtpConfig.cpp \
    src/Bluetoothctl.cpp \
    src/ViewModel/MassStorage.cpp \
    src/ViewModel/MultimediaConfig.cpp \
    src/ScreenSaverManager.cpp \
    src/ViewModel/ScreenSaver.cpp \
    src/ViewModel/NapiManager.cpp \
    src/ViewModel/SettingsScreenSaver.cpp \
    src/ViewModel/SettingsPackages.cpp \
    src/ViewModel/AlarmConfig.cpp \
    src/ViewModel/SettingsStatus.cpp


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
    src/ViewModel/MainWindow.h \
    src/ViewModel/SambaConfig.h \
    src/ViewModel/FtpConfig.h \
    src/Bluetoothctl.h \
    src/ViewModel/MassStorage.h \
    src/ViewModel/MultimediaConfig.h \
    src/ViewModel/Quotes.h \
    src/ScreenSaverManager.h \
    src/ViewModel/ScreenSaver.h \
    src/ViewModel/NapiManager.h \
    src/ViewModel/SettingsScreenSaver.h \
    src/ViewModel/SettingsPackages.h \
    src/ViewModel/AlarmConfig.h \
    src/ViewModel/SettingsStatus.h


FORMS +=

