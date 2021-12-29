TEMPLATE = lib
CONFIG += staticlib
CONFIG -= app_bundle
CONFIG += c++17
QT += quick

SOURCES += \
    src/ViewModel/alarmconfig.cpp \
    src/ViewModel/settings.cpp \
    src/editftpconfigfile.cpp \
    src/editwificonfigfile.cpp \
    src/editdlnaconfigfile.cpp \
    src/editmpdconfigfile.cpp \
    src/editscreensaverconfigfile.cpp \
    src/editalarmconfigfile.cpp \
    src/editheadersconfigfile.cpp \
    src/managementofexternaldevices.cpp

HEADERS += \
    src/ViewModel/alarmconfig.h \
    src/ViewModel/settings.h \
    src/editftpconfigfile.h \
    src/editwificonfigfile.h \
    src/editdlnaconfigfile.h \
    src/editmpdconfigfile.h \
    src/editscreensaverconfigfile.h \
    src/managementofexternaldevices.h \
    src/editalarmconfigfile.h \
    src/editheadersconfigfile.h
