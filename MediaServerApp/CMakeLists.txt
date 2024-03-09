cmake_minimum_required(VERSION 3.13)
project(MediaServerApp)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5DBus REQUIRED)
find_package(QtSystemd REQUIRED)

add_executable(${PROJECT_NAME}
    ViewModel/MainWindow/Bluetoothctl.cpp
    ViewModel/MainWindow/MainWindow.cpp
    ViewModel/Samba/SambaConfig.cpp
    ViewModel/Samba/SambaConfigExternalDevice1.cpp
    ViewModel/Samba/SambaConfigExternalDevice2.cpp
    ViewModel/Samba/SambaConfigExternalDevice3.cpp
    ViewModel/Samba/SambaConfigGlobal.cpp
    ViewModel/Samba/SambaConfigLocal.cpp
    ViewModel/ScreenSaver/ScreenSaver.cpp
    ViewModel/ScreenSaver/ScreenSaverManager.cpp
    ViewModel/Settings/SettingsPackages.cpp
    ViewModel/Settings/SettingsScreenSaver.cpp
    ViewModel/Settings/SettingsStatus.cpp
    ViewModel/AlarmConfig.cpp
    ViewModel/FtpConfig.cpp
    ViewModel/MassStorage.cpp
    ViewModel/MultimediaConfig.cpp
    ViewModel/NapiManager.cpp
    start.cpp
    resources/qml.qrc
)

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE
    ${CMAKE_SOURCE_DIR}/MediaServerLib
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    MediaServerLib
    QtSystemd
    Qt5::Quick
    Qt5::Widgets
    Qt5::DBus
    pthread
)

install(TARGETS ${PROJECT_NAME} DESTINATION "/opt")
