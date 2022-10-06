cmake_minimum_required(VERSION 3.13)
project(MediaServerLib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_library(${PROJECT_NAME}
        src/ViewModel/SettingsWifi.cpp
        src/ViewModel/SettingsIpAddress.cpp
        src/EditAlarmConfigFile.cpp
        src/EditScreenSaverConfigFile.cpp
        src/EditDlnaConfigFile.cpp
        src/EditWifiConfigFile.cpp
        src/EditFtpConfigFile.cpp
        src/ManagementYfExternalDevices.cpp
        src/EditMpdConfigFile.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC)

target_link_libraries(${PROJECT_NAME}
    Qt5::Quick
    Qt5::DBus
    QtSystemd
)
