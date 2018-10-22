include(gtest_dependency.pri)

TEMPLATE = app
#CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
#CONFIG -= qt

DEFINES += PATH_TO_TEST_FILES=\\\"$$PWD\\\"

HEADERS += \
    test.h \
    ../MediaServerApp/editfile.h

SOURCES += \
        main.cpp \
    editfiletest.cpp \
    ../MediaServerApp/editfile.cpp
