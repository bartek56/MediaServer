TEMPLATE = lib
CONFIG += staticlib
CONFIG -= app_bundle

SOURCES += \
    editftpconfigfile.cpp \
    editwificonfigfile.cpp \
    editdlnaconfigfile.cpp \
    editmpdconfigfile.cpp \
    editscreensaverconfigfile.cpp \
    editalarmconfigfile.cpp \
    editheadersconfigfile.cpp \
    managementofexternaldevices.cpp

HEADERS += \
    editftpconfigfile.h \
    editwificonfigfile.h \
    editdlnaconfigfile.h \
    editmpdconfigfile.h \
    editscreensaverconfigfile.h \
    managementofexternaldevices.h \
    editalarmconfigfile.h \
    editheadersconfigfile.h
