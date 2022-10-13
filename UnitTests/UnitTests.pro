include(gtest_dependency.pri)

TEMPLATE = app
#CONFIG += console
CONFIG -= app_bundle
CONFIG += thread

DEFINES += PATH_TO_TEST_FILES=\\\"$$PWD\\\"

HEADERS += \
    ../MediaServerLib/Utils/VectorData.h \
    ../MediaServerLib/ConfigFile/IFileManager.h \
    ../MediaServerLib/ConfigFile/AlarmConfigFile.h \
    ../MediaServerLib/ConfigFile/MpdConfigFile.h \
    Mock/MockFileManager.h

SOURCES += \
    ../MediaServerLib/Utils/VectorData.cpp \
    ../MediaServerLib/ConfigFile/AlarmConfigFile.cpp \
    ../MediaServerLib/ConfigFile/MpdConfigFile.cpp \
    AlarmConfigFileTest.cpp \
    MpdConfigFileTest.cpp \
    main.cpp
