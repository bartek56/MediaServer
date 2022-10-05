include(gtest_dependency.pri)

TEMPLATE = app
#CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
#CONFIG -= qt

DEFINES += PATH_TO_TEST_FILES=\\\"$$PWD\\\"

HEADERS += \
    ../MediaServerLib/src/editftpconfigfile.h \
    ../MediaServerLib/src/IFileManager.h

#    ../MediaServerApp/editdlnaconfigfile.h \
#    ../MediaServerApp/editmpdconfigfile.h \
#    ../MediaServerApp/editscreensaverconfigfile.h \
#    ../MediaServerApp/editftpconfigfile.h

SOURCES += \
        main.cpp \
    ../MediaServerLib/src/editftpconfigfile.cpp \
    ../MediaServerLib/src/editwificonfigfile.cpp \
    ../MediaServerLib/src/editdlnaconfigfile.cpp \
    ../MediaServerLib/src/editmpdconfigfile.cpp \
    ../MediaServerLib/src/editscreensaverconfigfile.cpp \
    Mock/mockfilemanager.cpp \
    editftpfiletest.cpp \
    editwififiletest.cpp \
    editdlnafiletest.cpp \
    editmpdfiletest.cpp \
    editscreensavefiletest.cpp
