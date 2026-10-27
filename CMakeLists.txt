cmake_minimum_required(VERSION 3.16)
project(MediaServer LANGUAGES CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Prefer Qt6, but keep the project buildable with Qt5 while downstream
# distributions transition to the newer Qt version.
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Quick Qml DBus Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Quick Qml DBus Network)

if(QT_VERSION_MAJOR EQUAL 6 AND Qt6_VERSION VERSION_LESS 6.3)
    message(FATAL_ERROR
        "Qt6.3 or newer is required because the QML compatibility layer uses FolderDialog.")
endif()

# -DCMAKE_FIND_DEBUG_MODE=1

# Example for a custom Qt installation:
# cmake -S . -B build -DCMAKE_PREFIX_PATH=/opt/Qt/6.6.3

add_subdirectory(MediaServerLib)
add_subdirectory(MediaServerStartup)
add_subdirectory(MediaServerApp)
add_subdirectory(Alarm)
add_subdirectory(UnitTests)
