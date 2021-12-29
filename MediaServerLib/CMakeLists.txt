cmake_minimum_required(VERSION 3.13)
project(MediaServerLib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_library(${PROJECT_NAME}
        src/ViewModel/alarmconfig.cpp
        src/ViewModel/settings.cpp
        src/editalarmconfigfile.cpp
        src/editscreensaverconfigfile.cpp
        src/editdlnaconfigfile.cpp
        src/editwificonfigfile.cpp
        src/editftpconfigfile.cpp
        src/managementofexternaldevices.cpp
        src/editheadersconfigfile.cpp
        src/editmpdconfigfile.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC)

target_link_libraries(${PROJECT_NAME}
    Qt5::Quick
)
