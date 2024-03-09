cmake_minimum_required(VERSION 3.13)
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
    ViewModel/SettingsWifi.cpp
    ViewModel/SettingsIpAddress.cpp
    ManagementOfExternalDevices.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC)

target_link_libraries(${PROJECT_NAME}
    Qt5::Quick
    Qt5::DBus
    QtSystemd
)
