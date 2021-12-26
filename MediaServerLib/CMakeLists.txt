cmake_minimum_required(VERSION 3.18)
project(MediaServerLib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_library(${PROJECT_NAME}
        ViewModel/alarmconfig.cpp
        ViewModel/settings.cpp
        editalarmconfigfile.cpp
        editscreensaverconfigfile.cpp
        editdlnaconfigfile.cpp
        editwificonfigfile.cpp
        editftpconfigfile.cpp
        managementofexternaldevices.cpp
        editheadersconfigfile.cpp
        editmpdconfigfile.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC)

target_link_libraries(${PROJECT_NAME}
    Qt5::Quick
)
