include(gtest_dependency.pri)

TEMPLATE = app
#CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
#CONFIG -= qt

DEFINES += PATH_TO_TEST_FILES=\\\"$$PWD\\\"

HEADERS += \
    ../MediaServerApp/editsambaconfigfile.h \
    ../MediaServerApp/editftpconfigfile.h

SOURCES += \
        main.cpp \
    ../MediaServerApp/editsambaconfigfile.cpp \
    ../MediaServerApp/editftpconfigfile.cpp \
    ../MediaServerApp/editwificonfigfile.cpp \
    editsambafiletest.cpp \
    editftpfiletest.cpp \
    editwififiletest.cpp
