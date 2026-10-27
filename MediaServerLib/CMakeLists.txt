cmake_minimum_required(VERSION 3.16)
project(MediaServerLib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_library(${PROJECT_NAME}
    ConfigFile/ConfigFile.cpp
    ConfigFile/AlarmConfigFile.cpp
    ConfigFile/DlnaConfigFile.cpp
    ConfigFile/FtpConfigFile.cpp
    ConfigFile/MpdConfigFile.cpp
    ConfigFile/ScreenSaverConfigFile.cpp
    ConfigFile/WifiConfigFile.cpp
    Utils/VectorData.cpp
    SystemdManager.h
    SystemdManager.cpp
    ViewModel/Settings/SettingsWifi.cpp
    ViewModel/Settings/SettingsIpAddress.cpp
    ManagementOfExternalDevices.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::DBus
)
