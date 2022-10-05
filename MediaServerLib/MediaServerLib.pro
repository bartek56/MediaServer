TEMPLATE = lib
CONFIG += staticlib
CONFIG -= app_bundle
CONFIG += c++17
QT += quick

LIBS += -lQtSystemd


SOURCES += \
    src/ViewModel/settingsIpAddress.cpp \
    src/ViewModel/settingsWifi.cpp \
    src/editftpconfigfile.cpp \
    src/editwificonfigfile.cpp \
    src/editdlnaconfigfile.cpp \
    src/mpdconfigfile.cpp \
    src/editmpdconfigfile.cpp \
    src/editscreensaverconfigfile.cpp \
    src/editalarmconfigfile.cpp \
    src/managementofexternaldevices.cpp

HEADERS += \
    src/ViewModel/settingsIpAddress.h \
    src/ViewModel/settingsWifi.h \
    src/editftpconfigfile.h \
    src/editwificonfigfile.h \
    src/editdlnaconfigfile.h \
    src/mpdconfigfile.h \
    src/editmpdconfigfile.h \
    src/editscreensaverconfigfile.h \
    src/managementofexternaldevices.h \
    src/editalarmconfigfile.h
