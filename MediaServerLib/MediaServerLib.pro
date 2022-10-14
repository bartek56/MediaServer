TEMPLATE = lib
CONFIG += staticlib
CONFIG -= app_bundle
CONFIG += c++17
QT += quick

LIBS += -lQtSystemd


SOURCES += \
    ConfigFile/AlarmConfigFile.cpp \
    ConfigFile/ConfigFile.cpp \
    ConfigFile/DlnaConfigFile.cpp \
    ConfigFile/FtpConfigFile.cpp \
    ConfigFile/MpdConfigFile.cpp \
    ConfigFile/ScreenSaverConfigFile.cpp \
    ConfigFile/WifiConfigFile.cpp \
    ViewModel/SettingsIpAddress.cpp \
    ViewModel/SettingsWifi.cpp \
    Utils/VectorData.cpp \
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
    ViewModel/SettingsIpAddress.h \
    ViewModel/SettingsWifi.h \
    Utils/VectorData.h \
    ManagementOfExternalDevices.h
