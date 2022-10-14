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
    ../MediaServerLib/ConfigFile/DlnaConfigFile.h \
    ../MediaServerLib/ConfigFile/ScreenSaverConfigFile.h \
    Mock/MockFileManager.h

SOURCES += \
    ../MediaServerLib/Utils/VectorData.cpp \
    ../MediaServerLib/ConfigFile/AlarmConfigFile.cpp \
    ../MediaServerLib/ConfigFile/MpdConfigFile.cpp \
    ../MediaServerLib/ConfigFile/DlnaConfigFile.cpp \
    ../MediaServerLib/ConfigFile/ScreenSaverConfigFile.cpp \
    AlarmConfigFileTest.cpp \
    MpdConfigFileTest.cpp \
    DlnaConfigFileTest.cpp \
    ScreenSaverConfigFileTest.cpp \
    main.cpp
