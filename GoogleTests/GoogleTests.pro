include(gtest_dependency.pri)



TEMPLATE = app
#CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
#CONFIG -= qt

HEADERS += \
    test.h \
    ../MediaServerApp/editfile.h

SOURCES += \
        main.cpp \
    editfiletest.cpp \
    ../MediaServerApp/editfile.cpp
