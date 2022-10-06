TEMPLATE = lib
CONFIG += staticlib
CONFIG -= app_bundle
CONFIG += c++17
QT += quick

LIBS += -lQtSystemd


SOURCES += \
    src/ViewModel/SettingsIpAddress.cpp \
    src/ViewModel/SettingsWifi.cpp \
    src/EditFtpConfigFile.cpp \
    src/EditWifiConfigFile.cpp \
    src/EditDlnaConfigFile.cpp \
    src/MpdConfigFile.cpp \
    src/EditMpdConfigFile.cpp \
    src/EditScreenSaverConfigFile.cpp \
    src/EditAlarmConfigFile.cpp \
    src/ManagementOfExternalDevices.cpp

HEADERS += \
    src/ViewModel/SettingsIpAddress.h \
    src/ViewModel/SettingsWifi.h \
    src/EditFtpConfigFile.h \
    src/EditWifiConfigFile.h \
    src/EditDlnaConfigFile.h \
    src/MpdConfigFile.h \
    src/EditMpdConfigFile.h \
    src/EditScreenSaverConfigFile.h \
    src/ManagementOfExternalDevices.h \
    src/EditAlarmConfigFile.h
