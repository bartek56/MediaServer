TEMPLATE = lib
CONFIG += staticlib
CONFIG -= app_bundle
CONFIG += c++14
QT += quick

SOURCES += \
    ViewModel/alarmconfig.cpp \
    ViewModel/settingsipaddress.cpp \
    ViewModel/settingsWifi.cpp \
    ViewModel/settingsstatus.cpp \
    editftpconfigfile.cpp \
    editwificonfigfile.cpp \
    editdlnaconfigfile.cpp \
    editmpdconfigfile.cpp \
    editscreensaverconfigfile.cpp \
    editalarmconfigfile.cpp \
    editheadersconfigfile.cpp \
    managementofexternaldevices.cpp

HEADERS += \
    ViewModel/alarmconfig.h \
    ViewModel/settings.h \
    editftpconfigfile.h \
    editwificonfigfile.h \
    editdlnaconfigfile.h \
    editmpdconfigfile.h \
    editscreensaverconfigfile.h \
    managementofexternaldevices.h \
    editalarmconfigfile.h \
    editheadersconfigfile.h
