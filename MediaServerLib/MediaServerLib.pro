TEMPLATE = lib
CONFIG += staticlib
CONFIG -= app_bundle
QT += quick

SOURCES += \
    ViewModel/alarmconfig.cpp \
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
    editftpconfigfile.h \
    editwificonfigfile.h \
    editdlnaconfigfile.h \
    editmpdconfigfile.h \
    editscreensaverconfigfile.h \
    managementofexternaldevices.h \
    editalarmconfigfile.h \
    editheadersconfigfile.h
