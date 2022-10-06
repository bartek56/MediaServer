include(gtest_dependency.pri)

TEMPLATE = app
#CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
#CONFIG -= qt

DEFINES += PATH_TO_TEST_FILES=\\\"$$PWD\\\"

HEADERS += \
    ../MediaServerLib/src/EditFtpConfigFile.h \
    ../MediaServerLib/src/IFileManager.h

    Mock/MockFileManager.h \

#    ../MediaServerApp/editdlnaconfigfile.h \
#    ../MediaServerApp/editmpdconfigfile.h \
#    ../MediaServerApp/editscreensaverconfigfile.h \
#    ../MediaServerApp/editftpconfigfile.h

SOURCES += \
        main.cpp \
    ../MediaServerLib/src/EditFtpConfigFile.cpp \
    ../MediaServerLib/src/EditWifiConfigFile.cpp \
    ../MediaServerLib/src/EditDlnaConfigFile.cpp \
    ../MediaServerLib/src/EditMpdConfigFile.cpp \
    ../MediaServerLib/src/EditScreenSaverConfigFile.cpp \
    EditFtpFileTest.cpp \
    EditWifiFileTest.cpp \
    EditDlnaFileTest.cpp \
    EditMpdFileTest.cpp \
    EditScreenSaverFileTest.cpp
