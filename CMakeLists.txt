cmake_minimum_required(VERSION 3.14)
project(MediaServer)

#find_package(Qt5 COMPONENTS Core Widgets Quick REQUIRED PATHS /opt/qt5.15.2/lib/cmake/)
find_package(Qt5 COMPONENTS Core Widgets Quick)
add_subdirectory(MediaServerLib)
add_subdirectory(MediaServerStartup)
add_subdirectory(MediaServerApp)
add_subdirectory(Alarm)
