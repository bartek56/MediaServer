include(gtest_dependency.pri)

TEMPLATE = app
#CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
#CONFIG -= qt

DEFINES += PATH_TO_TEST_FILES=\\\"$$PWD\\\"

HEADERS += \
    ../MediaServerApp/editsambaconfigfile.h \
    ../MediaServerApp/editdlnaconfigfile.h \
    ../MediaServerApp/editmpdconfigfile.h \
    ../MediaServerApp/editscreensaverconfigfile.h \
    ../MediaServerApp/editftpconfigfile.h

SOURCES += \
        main.cpp \
    ../MediaServerApp/editsambaconfigfile.cpp \
    ../MediaServerApp/editftpconfigfile.cpp \
    ../MediaServerApp/editwificonfigfile.cpp \
    ../MediaServerApp/editdlnaconfigfile.cpp \
    ../MediaServerApp/editmpdconfigfile.cpp \
    ../MediaServerApp/editscreensaverconfigfile.cpp \
    editsambafiletest.cpp \
    editftpfiletest.cpp \
    editwififiletest.cpp \
    editdlnafiletest.cpp \
    editmpdfiletest.cpp \
    editscreensavefiletest.cpp
