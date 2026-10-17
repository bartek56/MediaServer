TEMPLATE = lib
CONFIG += staticlib
CONFIG -= app_bundle
CONFIG += c++17
QT += core quick dbus


SOURCES += \
    ConfigFile/AlarmConfigFile.cpp \
    ConfigFile/ConfigFile.cpp \
    ConfigFile/DlnaConfigFile.cpp \
    ConfigFile/FtpConfigFile.cpp \
    ConfigFile/MpdConfigFile.cpp \
    ConfigFile/ScreenSaverConfigFile.cpp \
    ConfigFile/WifiConfigFile.cpp \
    ViewModel/Settings/SettingsIpAddress.cpp \
    ViewModel/Settings/SettingsWifi.cpp \
    Utils/VectorData.cpp \
    SystemdManager.cpp \
    ManagementOfExternalDevices.cpp

HEADERS += \
    ConfigFile/IConfigFile.h \
    ConfigFile/AlarmConfigFile.h \
    ConfigFile/ConfigFile.h \
    ConfigFile/DlnaConfigFile.h \
    ConfigFile/FtpConfigFile.h \
    ConfigFile/IFileManager.h \
    ConfigFile/MpdConfigFile.h \
    ConfigFile/ScreenSaverConfigFile.h \
    ConfigFile/WifiConfigFile.h \
    ViewModel/Settings/SettingsIpAddress.h \
    ViewModel/Settings/SettingsWifi.h \
    Utils/VectorData.h \
    SystemdManager.h \
    ManagementOfExternalDevices.h
